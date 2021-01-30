# the main bidding bot file WIP
# testing some APIs and getting a hang of things

import pandas as pd
import utils,sharpe,recommendations
from securities import build_securities

def main():
    # securities = build_securities()
    # intdict = recommendations.build_intervals()
    # recommendations.print_recommendations(intdict,securities)
    securities = utils.get_sp500()
    sharpe.print_portolio(securities,100,True)
    

if __name__ == "__main__":
    main()