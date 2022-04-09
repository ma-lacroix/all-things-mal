// Trying out structs, traits and generic functions in Rust

struct HumanCreator {
    name: String,
    animal_type: String,
    age: i32,
}
struct AnimalCreator {
    name: String,
    animal_type: String,
    age: i32,
}
trait Getters {
    fn get_name(self: &mut Self);
    fn get_type(self: &mut Self);
    fn get_age(self: &mut Self);
}
trait IncrAge {
    fn incr_age(self: &mut Self, val: i32);
}

impl Getters for AnimalCreator {
    // TODO: not really getters
    fn get_name(self: &mut Self) {
        println!("{}",self.name);
    }
    fn get_type(self: &mut Self) {
        println!("{}",self.animal_type);
    }
    fn get_age(self: &mut Self) {
        println!("{}",self.age);
    }
}

impl Getters for HumanCreator {
    // TODO: not really getters
    fn get_name(self: &mut Self) {
        println!("{}",self.name);
    }
    fn get_type(self: &mut Self) {
        println!("{}",self.animal_type);
    }
    fn get_age(self: &mut Self) {
        println!("{}",self.age);
    }
}

impl IncrAge for AnimalCreator {
    fn incr_age(&mut self, val: i32) {
        self.age += val;
        self.get_age();
    }
}
impl IncrAge for HumanCreator {
    fn incr_age(&mut self, val: i32) {
        self.age *= val;
        self.get_age();
    }
}

fn super_incr<T: IncrAge>(mut item: T, val: i32) {
    for _i in 0..=10 {
        item.incr_age(val);
    }
    println!("Done.\n");
}

fn main() {
    animals::say_hi();
    let tig: AnimalCreator = AnimalCreator {name : "Tigger".to_string(),
                                    animal_type : "Tiger".to_string(),
                                    age: 10 };
    let ma: HumanCreator = HumanCreator {name : "M-A".to_string(),
        animal_type : "HumanMale".to_string(),
        age: 39 };
    super_incr(tig,3);
    super_incr(ma,3);
}
