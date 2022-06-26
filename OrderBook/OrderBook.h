
//------------------------------//
//   OrderBook.h
//   by YueZhengZheng
//   @ 2022.06.26
//------------------------------//


#ifndef _ORDER_BOOK_H_
#define _ORDER_BOOK_H_

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <map>
#include <list>

using namespace std;


enum ORDER_ACTION
{
    OA_ADD = 'A',
    OA_DEL = 'X',
    OA_MOD = 'M'
};

enum ORDER_SIDE
{
    OS_ASK = 'S',
    OS_BID = 'B'
};


/***** TradeAction *****/
class TradeAction
{
public:
    TradeAction(string action_line);
    ~TradeAction();

    bool ParseActionLine();
    unsigned int GetAction() {return m_action;};
    unsigned int GetID() {return m_id;};
    unsigned int GetSide() {return m_side;};
    unsigned int GetVolume() {return m_volume;};
    unsigned int GetPrice() {return m_price;};

private:
    vector<string> m_action_param;
    bool m_legal;
    unsigned int m_action;
    unsigned int m_id;
    unsigned int m_side;
    unsigned int m_volume;
    unsigned int m_price;
};

/***** Order *****/
class Order
{
public:
    Order() {};
    ~Order() {};

    void SetID(unsigned int id) {m_id = id;};
    void SetSide(unsigned int side) {m_side = side;};
    void SetVolume(unsigned int volume) {m_volume = volume;};
    void SetPrice(unsigned int price) {m_price = price;};

    unsigned int GetID() {return m_id;};
    unsigned int GetSide() {return m_side;};
    unsigned int GetVolume() {return m_volume;};
    unsigned int GetPrice() {return m_price;};

private:
    unsigned int m_id;
    unsigned int m_side;
    unsigned int m_volume;
    unsigned int m_price;
};


/***** OrderBook *****/
class OrderBook
{
public:
    OrderBook() {};
    ~OrderBook() {};

    void UpdateOrderBook(TradeAction &trade_action);
    bool MakeDeal();
    void ShowState();

private:
    map< unsigned int, list<Order> > ask_order_map;
    map< unsigned int, list<Order> > bid_order_map;
};


#endif
