# collection of tools to analyse stock information

import datetime
import pandas as pd
import numpy as np
from tradingview_ta import TA_Handler, Interval
import pandas_datareader.data as web
import sharpe,recommendations

def get_sp500():    
    df=pd.read_html('https://en.wikipedia.org/wiki/List_of_S%26P_500_companies')[0]
    return df

def build_intervals():
    
    oneday = Interval.INTERVAL_1_DAY
    oneweek = Interval.INTERVAL_1_WEEK
    onemonth = Interval.INTERVAL_1_MONTH
    intdict = {"1d":[oneday,"last day"],"1w":[oneweek,"last week"],"1m":[onemonth,"last month"]}
    
    return intdict

def get_securities_list(securities):
    symb_list = []
    for item in securities:
        symb_list.append(securities[item][1][0])
    return symb_list

def get_close_prices(timeframe,security):
    service = 'yahoo'
    end = datetime.datetime.today().strftime('%Y-%m-%d')    
    if(timeframe=='1d'):
        start = (datetime.datetime.today()-datetime.timedelta(days=2)).strftime('%Y-%m-%d')
    elif(timeframe=='1w'):
        start = (datetime.datetime.today()-datetime.timedelta(days=8)).strftime('%Y-%m-%d')
    elif(timeframe=='1m'):
        start = (datetime.datetime.today()-datetime.timedelta(days=31)).strftime('%Y-%m-%d')
    elif(timeframe=='3m'):
        start = (datetime.datetime.today()-datetime.timedelta(days=93)).strftime('%Y-%m-%d')
    else:
        start = end
    try:
        df = np.round(web.DataReader(security,service,start,end)[['Close','Volume']],2)
        df.sort_values('Date',inplace = True)
    except ValueError as error:
        print("Couldn't connect to {} - {}".format(service,error))
    return df

def print_recommendations(intdict,securities):
    print("\nToday's date: {}\r".format(datetime.date.today()))
    print(get_close_prices('1d',get_securities_list(securities))['Close'].tail(1))
    for intd in intdict:
        for item in securities:    
            print("\n{}".format(securities[item][1][0]))
            try:
                recom = recommendations.get_recommendation(securities[item][0],securities[item][1],intdict[intd][0])
                print("Based on {} -> {}".format(intdict[intd][1],recom))
            except ValueError as error:
                print("Couldn't connect to TradingView - {}".format(error))
        print("\r")

def print_portolio(intdict,securities,simulations):
    print("\nToday's date: {}\r".format(datetime.date.today()))
    try:
        if(type(securities)==dict):
            symb_list = get_securities_list(securities)
        elif(type(securities)==list):
            symb_list = securities
        else:
            print("Wrong stock symbols data type - must be a list of dict")
            symb_list = []
        sol = sharpe.get_sharp_ratio(simulations,sharpe.get_log_ret('3m',symb_list))
        print("Optimal portfolio allocation (based on last 3 months): ")
        for row in zip(symb_list,sol):
            print(row[0],': ',row[1])
    except ValueError as error:
        print("Couldn't get Sharpe ratios - {}".format(error))
