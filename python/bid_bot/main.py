# the main bidding bot file WIP
# testing some APIs and getting a hang of things

import datetime
import pandas
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

    secdict = {"1":[BKNG,["BKNG","NASDAQ","america"]],
               "2":[TSLA,["TSLA","NASDAQ","america"]],
               "3":[AMZN,["AMZN","NASDAQ","america"]],
               "4":[BBBY,["BBBY","NASDAQ","america"]]
                }
    
    return secdict

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
        start = (datetime.datetime.today()-datetime.timedelta(days=1)).strftime('%Y-%m-%d')
    elif(timeframe=='1w'):
        start = (datetime.datetime.today()-datetime.timedelta(days=7)).strftime('%Y-%m-%d')
    elif(timeframe=='1m'):
        start = (datetime.datetime.today()-datetime.timedelta(days=30)).strftime('%Y-%m-%d')
    else:
        start = end
    try:
        df = web.DataReader(security,service,start,end)[['Close','Volume']]
    except ValueError as error:
        print("Couldn't connect to {} - {}".format(service,error))
    return df

def print_results(intdict,securities):
    print("\nToday's date: {}\r".format(datetime.date.today()))
    for item in securities:
        print("\n{}\n".format(securities[item][1][0]))
        for intd in intdict:
            df = get_close_prices(intd,securities[item][1][0])
            try:
                recom = get_recommendation(securities[item][0],securities[item][1],intdict[intd][0])
            except ValueError as error:
                print("Couldn't connect to TradingView - {}".format(error))
            print("Based on {} -> {}\n".format(intdict[intd][1],recom))
            print(df)
        print("\r")

def main():
    securities = build_securities()
    intdict = build_intervals()
    print_results(intdict,securities)

if __name__ == "__main__":
    main()