// Testing out Rust stuff
// simple app that can generate a booking from the command line
#![allow(unused_variables, unused_mut, dead_code)]

fn main() {
    // args must have destination, checking date, checkout date, payment method & maximum price
    // let args: Vec<String> = std::env::args().skip(1).collect();
    // let price: i32 = std::env::args().skip(4).collect();

    let mut booking = Accomodation {
        destination: "Montreal".to_string(),
        checking_date: "2022-07-15".to_string(),
        checkout_date: "2022-08-04".to_string(),
        payment_method: PaymentMethod::CreditCard,
        max_price: 100 };

    let mut exp = Experience {
        name: "Museum".to_string(),
        exp_date: "2022-07-25".to_string(),
        payment_method: PaymentMethod::BankTransfer,
        price: 13 };

    if check(&mut booking) {
        print_method(&mut booking);
        let some_var: i32 = adj_fee(&mut booking);
        println!("{}", some_var.to_string());
    }

    if check(&mut exp) {
        print_method(&mut exp);
        let some_var: i32 = adj_fee(&mut exp);
        println!("{}", some_var.to_string());
    }

    let some_var: i32 = booking.adjust_fees();
    println!("{}", some_var.to_string());
}

enum PaymentMethod {
    CreditCard,
    BankTransfer,
    PayPal,
}

impl PaymentMethod {
    fn get_name(&self) -> String {
        let name:String = match self {
            PaymentMethod::CreditCard => "credit_card".to_string(),
            PaymentMethod::BankTransfer => "bank_transfer".to_string(),
            PaymentMethod::PayPal => "Paypal".to_string(),
        };
        name
    }
    fn get_fees(&self) -> i32 {
        let fee:i32 = match self {
            PaymentMethod::CreditCard => 3,
            PaymentMethod::BankTransfer => 5,
            PaymentMethod::PayPal => 1,
        };
        fee
    }
}

struct Accomodation {

    destination: String,
    checking_date: String,
    checkout_date: String,
    payment_method: PaymentMethod,
    max_price: i32,

}

struct Experience {
    name: String,
    exp_date: String,
    price: i32,
    payment_method: PaymentMethod,
}

trait BookingUtils {
    fn check_data(self: &Self) -> bool;
    fn print_payment_method(self: &Self);
    fn adjust_fees(self: &mut Self) -> i32;
}

impl BookingUtils for Accomodation {

    fn check_data(&self) -> bool {
        if self.checking_date.contains("-") &&
            self.checkout_date.contains("-") &&
            self.max_price > 0 {
            println!("Booking data is good");
            true
        } else {
            println!("Booking data is bad");
            false
        }
    }
    fn print_payment_method(&self) {
        println!("{}", self.payment_method.get_name());
    }
    fn adjust_fees(self: &mut Self) -> i32 {
        self.payment_method.get_fees()*2
    }
}

impl BookingUtils for Experience {

    fn check_data(&self) -> bool {
        if self.exp_date.contains("-") &&
            self.price > 0 {
            println!("Experience data is good");
            true
        } else {
            println!("Experience data is bad");
            false
        }
    }
    fn print_payment_method(&self) {
        println!("{}", self.payment_method.get_name());
    }
    fn adjust_fees(self: &mut Self) -> i32 {
        self.payment_method.get_fees()
    }
}

fn print_method<T: BookingUtils>(item: &mut T) {
    item.print_payment_method();
}

fn check<T: BookingUtils>(item: &mut T) -> bool {
    item.check_data()
}

fn adj_fee<T: BookingUtils>(item: &mut T) -> i32 {
    item.adjust_fees()
}