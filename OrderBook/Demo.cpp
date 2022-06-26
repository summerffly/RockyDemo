
//------------------------------//
//   Demo.cpp
//   by YueZhengZheng
//   @ 2022.06.26
//------------------------------//

#include <queue>
#include "OrderBook.h"

using namespace std;


queue<TradeAction> action_queue;
OrderBook order_book;

void InputLine(TradeAction &trade_action)
{
    string input;
    getline(cin, input);
    trade_action = TradeAction(input);
}

int main(int argc, char **argv, char *env[])
{
    TradeAction trade_action("");
    while( 1 )
    {
        InputLine(trade_action);
        if(trade_action.ParseActionLine() == true)
        {
            //
            action_queue.push(trade_action);
            //
            order_book.UpdateOrderBook(trade_action);
            while(order_book.MakeDeal())
                cout << "Deal" << endl;
            order_book.ShowState();
        }
        else
        {
            cout << "=================" << endl;
            cout << "Illegal Input !!!" << endl;
            cout << "=================" << endl;
        }
    }

    return 0;
}
