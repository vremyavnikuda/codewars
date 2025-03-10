fn main() {
    let user = StructUserTuple {
        name: "Andrew",
        age: 30,
        height: 1.82,
    };
    println!("{}", user.name());
    println!("{}", user.age());
    println!("{}", user.height());
    arr_();
    arr_1();
    copy_arr();
    struct_user_fn();
}

struct StructUserTuple<'a> {
    name: &'a str,
    age: i32,
    height: f32,
}

trait User {
    fn name(&self) -> &str;
    fn age(&self) -> i32;
    fn height(&self) -> f32;
}

impl User for StructUserTuple<'_> {
    fn name(&self) -> &str {
        &self.name
    }
    fn age(&self) -> i32 {
        self.age
    }
    fn height(&self) -> f32 {
        self.height
    }
}

fn arr_() {
    let number: [i32; 2] = [1, 2];
    println!("{:?}", number[0]);
    println!("{:?}", number[1]);
}

fn arr_1() {
    let new_array: [i32; 5] = [1, 2, 3, 4, 5];
    for number in new_array {
        println!("{}", number);
    }
    println!("Длина массива new_array:{}", new_array.len());
}

fn copy_arr() {
    let new_array: [i32; 5] = [1, 2, 3, 4, 5];
    let copy_new_array = new_array;
    println!("{:?}", copy_new_array);
}

struct User_Struct {
    name: String,
    age: i32,
}

fn struct_user_fn() {
    let user = User_Struct {
        name: "Andrew".to_string(),
        age: 30,
    };

    let User_Struct { name: user_name, age: user_age } = user;
    println!("{},{}", user_name, user_age);
}
