fn main(){
    let user = StructUserTuple{
        name: "Andrew",
        age: 30,
        height: 1.82,
    };
    println!("{}",user.name());
    println!("{}",user.age());
    println!("{}",user.height());
    arr_();
}

struct StructUserTuple<'a>{
    name: &'a str,
    age: i32,
    height: f32,
}

trait User{
    fn name(&self)->&str;
    fn age(&self)->i32;
    fn height(&self)->f32;
}

impl User for StructUserTuple<'_> {
    fn name(&self)->&str{
        &self.name
    }
    fn age(&self)->i32{
        self.age
    }
    fn height(&self)->f32{
        self.height
    }
}

fn arr_(){
    let number:[i32;2]=[1,2];
    println!("{:?}",number[0]);
    println!("{:?}",number[1]);
}
