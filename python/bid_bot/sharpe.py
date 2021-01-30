# Using the Sharpe ratio, the 

import datetime
import pandas as pd
import numpy as np
import pandas_datareader.data as web
import utils

def get_sharp_ratio(simulations,df):
    print("\nGetting Sharpe ratios...\n")
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
    return np.round(all_weights[sharpe_arr.argmax(),:],3)

def get_log_ret(intdict,symb_list):
    df = utils.get_close_prices(intdict,symb_list)
    log_ret = pd.DataFrame(np.log(df['Close']/df['Close'].shift(1)))
    log_ret.fillna(0,inplace=True)
    return log_ret
