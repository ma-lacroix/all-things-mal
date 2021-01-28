# the main bidding bot file WIP
# testing some APIs and getting a hang of things

import datetime
import pandas as pd
import numpy as np
from tradingview_ta import TA_Handler, Interval
import pandas_datareader.data as web

def build_intervals():
    
    oneday = Interval.INTERVAL_1_DAY
    oneweek = Interval.INTERVAL_1_WEEK
    onemonth = Interval.INTERVAL_1_MONTH
    intdict = {"1d":[oneday,"last day"],"1w":[oneweek,"last week"],"1m":[onemonth,"last month"]}
    
    return intdict

def build_securities():

    BKNG = TA_Handler()
    TSLA = TA_Handler()
    AMZN = TA_Handler()
    BBBY = TA_Handler()
    HELE = TA_Handler()
    GGG = TA_Handler()
    EXPD = TA_Handler()
    GRMN = TA_Handler()
    TSM = TA_Handler()

    secdict = {"1":[BKNG,["BKNG","NASDAQ","america"]],
               "2":[TSLA,["TSLA","NASDAQ","america"]],
               "3":[AMZN,["AMZN","NASDAQ","america"]],
               "4":[BBBY,["BBBY","NASDAQ","america"]],
               "5":[HELE,["HELE","NASDAQ","america"]],
               "6":[GGG,["GGG","NYSE","america"]],
               "7":[EXPD,["EXPD","NASDAQ","america"]],
               "8":[GRMN,["GRMN","NASDAQ","america"]],
               "9":[TSM,["TSM","NYSE","america"]]
                }
    
    return secdict

def get_securities_list(securities):
    symb_list = []
    for item in securities:
        symb_list.append(securities[item][1][0])
    return symb_list

def get_recommendation(var,meta,intv):
    var.set_symbol_as(meta[0])
    var.set_exchange_as_crypto_or_stock(meta[1])
    var.set_screener_as_stock(meta[2])
    var.set_interval_as(intv)
    
    return var.get_analysis().summary["RECOMMENDATION"]

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

def get_sharp_ratio(simulations,df):
    print("\nGetting optimal portfolio distribution\n{}".format(list(df.columns)))
    all_weights = np.zeros((simulations,len(df.columns)))
    ret_arr = np.zeros(simulations)
    vol_arr = np.zeros(simulations)
    sharpe_arr = np.zeros(simulations)

    for ind in range(simulations):
        weights = np.array(np.random.random(len(df.columns)))
        weights = weights / np.sum(weights)
        all_weights[ind,:] = weights
        ret_arr[ind] = np.sum((df.mean() * weights) *len(df))
        vol_arr[ind] = np.sqrt(np.dot(weights.T, np.dot(df.cov() * len(df), weights)))
        sharpe_arr[ind] = ret_arr[ind]/vol_arr[ind]
    return all_weights[sharpe_arr.argmax(),:]

def get_log_ret(intdict,securities):
    symb_list = get_securities_list(securities)
    df = get_close_prices(intdict,symb_list)
    log_ret = pd.DataFrame(np.log(df['Close']/df['Close'].shift(1)))
    log_ret.fillna(0,inplace=True)
    return log_ret

def print_results(intdict,securities):
    print("\nToday's date: {}\r".format(datetime.date.today()))
    print(get_close_prices('1d',get_securities_list(securities))['Close'].tail(1))
    for intd in intdict:
        for item in securities:    
            print("\n{}".format(securities[item][1][0]))
            try:
                recom = get_recommendation(securities[item][0],securities[item][1],intdict[intd][0])
                print("Based on {} -> {}".format(intdict[intd][1],recom))
            except ValueError as error:
                print("Couldn't connect to TradingView - {}".format(error))
        print("\r")
    try:
        sol = get_sharp_ratio(15000,get_log_ret('3m',securities))
        print("Optimal portfolio allocation (based on last 3 months): {}".format(sol))
    except ValueError as error:
        print("Couldn't get Sharpe ratios - {}".format(error))

def main():
    securities = build_securities()
    intdict = build_intervals()
    print_results(intdict,securities)

if __name__ == "__main__":
    main()