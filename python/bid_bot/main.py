# Personal stock portfolio creator WIP
# Author: Marc-Antoine Lacroix

import pandas as pd
import utils,sharpe,recommendations
from securities import build_securities

def main():
    # securities = build_securities()
    # intdict = recommendations.build_intervals()
    # recommendations.print_recommendations(intdict,securities)
    securities = utils.trim_too_expensive(utils.get_sp500(),100)
    sharpe.print_portolio(securities,100,True)
    
if __name__ == "__main__":
    main()