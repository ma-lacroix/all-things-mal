# collection of tools to analyse stock information

import datetime
import pandas as pd
import numpy as np
import pandas_datareader.data as web
import sharpe,recommendations

def get_sp500():
    print("Getting list of S&P stock symbols...")        
    df=pd.read_html('https://en.wikipedia.org/wiki/List_of_S%26P_500_companies')[0][['GICS Sub-Industry','GICS Sector','Symbol']]
    return df

def check_dtype_securities(securities):
    if(type(securities)==dict):
        symb_list = recommendations.get_securities_list(securities)
    elif(type(securities)==list):
        symb_list = securities
    elif(type(securities)==pd.core.frame.DataFrame):
        symb_list = securities['Symbol'].head(30)
    else:
        print("Wrong stock symbols data type - must be a list of dict")
        symb_list = []
    return symb_list


def get_start(timeframe):
    if(timeframe=='1d'):
        start = (datetime.datetime.today()-datetime.timedelta(days=2)).strftime('%Y-%m-%d')
    elif(timeframe=='1w'):
        start = (datetime.datetime.today()-datetime.timedelta(days=8)).strftime('%Y-%m-%d')
    elif(timeframe=='1m'):
        start = (datetime.datetime.today()-datetime.timedelta(days=31)).strftime('%Y-%m-%d')
    elif(timeframe=='3m'):
        start = (datetime.datetime.today()-datetime.timedelta(days=93)).strftime('%Y-%m-%d')
    else:
        start = datetime.datetime.today().strftime('%Y-%m-%d')
    return start

def get_close_prices(timeframe,security):    
    service = 'yahoo'
    start = get_start(timeframe)
    end = datetime.datetime.today().strftime('%Y-%m-%d')    
    try:
        print("Getting closing prices...")
        df = np.round(web.DataReader(security,service,start,end)[['Close','Volume']],2)
        df.sort_values('Date',inplace = True)
    except ValueError as error:
        print("Couldn't connect to {} - {}".format(service,error))
    return df
