# functions to pull TV_Handler library recommendations

import datetime
import pandas as pd
import numpy as np
from tradingview_ta import TA_Handler, Interval
import utils

def build_intervals():
    # TA_handler class member variables
    oneday = Interval.INTERVAL_1_DAY
    oneweek = Interval.INTERVAL_1_WEEK
    onemonth = Interval.INTERVAL_1_MONTH
    intdict = {"1d":[oneday,"last day"],"1w":[oneweek,"last week"],"1m":[onemonth,"last month"]}
    
    return intdict

def get_recommendation(var,meta,intv):
    var.set_symbol_as(meta[0])
    var.set_exchange_as_crypto_or_stock(meta[1])
    var.set_screener_as_stock(meta[2])
    var.set_interval_as(intv)
    
    return var.get_analysis().summary["RECOMMENDATION"]

def get_securities_list(securities):
    symb_list = []
    for item in securities:
        symb_list.append(securities[item][1][0])
    return symb_list

def print_recommendations(intdict,securities):
    print("\nToday's date: {}\r".format(datetime.date.today()))
    # prices = utils.get_close_prices('1d',get_securities_list(securities))['Close'].tail(1)
    for intd in intdict:
        for item in securities:    
            print("\n{}".format(securities[item][1][0]))
            try:
                recom = get_recommendation(securities[item][0],securities[item][1],intdict[intd][0])
                print("Based on {} -> {}".format(intdict[intd][1],recom))
                                                            # prices[['Symbols']==item])
            except ValueError as error:
                print("Couldn't connect to TradingView - {}".format(error))
        print("\r")

