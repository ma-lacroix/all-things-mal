from tradingview_ta import TA_Handler, Interval

def build_securities():
# smaple portolio dictionary - WIP

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