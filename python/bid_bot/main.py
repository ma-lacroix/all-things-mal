# the main bidding bot file WIP
# testing some APIs and getting a hang of things

import datetime
from tradingview_ta import TA_Handler, Interval

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

def print_results(intdict,securities):
    print("\nToday's date: {}\r".format(datetime.date.today()))
    for intd in intdict:
        print("Based on {}\n".format(intdict[intd][1]))
        for item in securities:
            recom = get_recommendation(securities[item][0],securities[item][1],intdict[intd][0])
            print("{} -> {}".format(securities[item][1][0],recom))
        print("\r")

def main():
    securities = build_securities()
    intdict = build_intervals()
    print_results(intdict,securities)

if __name__ == "__main__":
    main()