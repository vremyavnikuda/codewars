fn main() {
    let _andrew = create_person("Andrew".to_string(), "andrew".to_string(), 123);
    print_struct(&_andrew);
}

struct Person {
    name: String,
    login: String,
    password: i32,
}

fn print_struct(person: &Person) {
    println!("{}:{}:{}", person.name, person.login, person.password);
}

fn create_person(name: String, login: String, password: i32) -> Person {
    Person { name, login, password }
}
