
//------------------------------//
//   OrderBook.cpp
//   by YueZhengZheng
//   @ 2022.06.26
//------------------------------//

#include "OrderBook.h"


TradeAction::TradeAction(string action_line)
{
    char *strline = new char[action_line.size()+1];
	strcpy(strline, action_line.c_str());

    m_action_param.clear();
	const char *delim = ",";
	char *p = strtok(strline, delim);
	while(p)
    {
		string s = p;
		m_action_param.push_back(s);
		p = strtok(NULL, delim);
    }

    delete []strline;

    m_legal = true;
    m_action = 0;
    m_id = 0;
    m_side = 0;
    m_volume = 0;
    m_price = 0;
}

TradeAction::~TradeAction()
{
    //
}

bool TradeAction::ParseActionLine()
{
    if(m_action_param.size() != 5)
        m_legal = false;

    if(m_action_param[0] == "A")
        m_action = OA_ADD;
    else if(m_action_param[0] == "X")
        m_action = OA_DEL;
    else if(m_action_param[0] == "M")
        m_action = OA_MOD;
    else
        m_legal = false;

    m_id = atoi(m_action_param[1].c_str());

    if(m_action_param[2] == "S")
        m_side = OS_ASK;
    else if(m_action_param[2] == "B")
        m_side = OS_BID;
    else
        m_legal = false;

    m_volume = atoi(m_action_param[3].c_str());
    m_price = atoi(m_action_param[4].c_str());

    return m_legal;
}


void OrderBook::UpdateOrderBook(TradeAction &trade_action)
{
    //cout << trade_action.GetAction() << "," << trade_action.GetID() << "," \
    //<< trade_action.GetVolume() << "," << trade_action.GetPrice() << endl;

    if(trade_action.GetAction() == OA_ADD)
    {
        Order new_order;
        new_order.SetID(trade_action.GetID());
        new_order.SetPrice(trade_action.GetPrice());
        new_order.SetSide(trade_action.GetSide());
        new_order.SetVolume(trade_action.GetVolume());

        if(new_order.GetSide() == OS_ASK)
        {
            map< unsigned int, list<Order> >::iterator iter_map = ask_order_map.find(trade_action.GetPrice());
            if(iter_map == ask_order_map.end())
            {
                list<Order> order_list;
                order_list.push_back(new_order);
                ask_order_map[trade_action.GetPrice()] = order_list;
            }
            else
            {
                iter_map->second.push_back(new_order);
            }
        }
        else if(new_order.GetSide() == OS_BID)
        {
            map< unsigned int, list<Order> >::iterator iter_map = bid_order_map.find(trade_action.GetPrice());
            if(iter_map == bid_order_map.end())
            {
                list<Order> order_list;
                order_list.push_back(new_order);
                bid_order_map[trade_action.GetPrice()] = order_list;
            }
            else
            {
                iter_map->second.push_back(new_order);
            }
        }
    }
    else if(trade_action.GetAction() == OA_DEL)
    {
        //
    }
    else if(trade_action.GetAction() == OA_MOD)
    {
        //
    }
    else
    {
        //
    }
}

bool OrderBook::MakeDeal()
{
    return false;
}

void OrderBook::ShowState()
{
    cout << "=================" << endl;
    cout << "ASK" << endl;
    if(ask_order_map.size() == 0)
        cout << " " << endl;

    map< unsigned int, list<Order> >::iterator iter_map = ask_order_map.begin();
    for(; iter_map!=ask_order_map.end(); iter_map++)
    {
        cout << iter_map->first << ": ";
        list<Order>::iterator iter_list = iter_map->second.begin();
        for(; iter_list!=iter_map->second.end(); iter_list++)
            cout << iter_map->second.front().GetVolume() << " ";
        cout << endl;
    }

    cout << "------------" << endl;
    if(bid_order_map.size() == 0)
        cout << " " << endl;

    iter_map = bid_order_map.end();
    while( bid_order_map.size() != 0 )
    {
        iter_map--;
        cout << iter_map->first << ": ";
        list<Order>::iterator iter_list = iter_map->second.begin();
        for( ; iter_list != iter_map->second.end(); iter_list++)
            cout << iter_list->GetVolume() << " ";
        cout << endl;
        if(iter_map==bid_order_map.begin())
            break;
    }

    cout << "BID" << endl;
    cout << "=================" << endl;
}
