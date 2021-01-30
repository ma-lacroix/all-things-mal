# functions to pull TV_Handler library recommendations

import datetime
import pandas as pd
import numpy as np
from tradingview_ta import TA_Handler, Interval
import utils

def get_recommendation(var,meta,intv):
    var.set_symbol_as(meta[0])
    var.set_exchange_as_crypto_or_stock(meta[1])
    var.set_screener_as_stock(meta[2])
    var.set_interval_as(intv)
    
    return var.get_analysis().summary["RECOMMENDATION"]