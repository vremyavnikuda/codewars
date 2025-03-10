fn main(){
    let user = ("Andrew",30,1.82);
    user.display(1);
}

fn tuple_fn()->(&'static str,i32,f32){
    let user:(&str,i32,f32)=("Andrew",30,1.82);
    user
}

fn decomposition_tuple(user:(&str,i32,f32)){
    let (name,age,height)= user;
    println!("Name:{}",name);
    println!("Age:{}",age);
    println!("Height:{}",height);
}

trait Display {
    fn display(&self,index:usize);
}

struct User{
    name: String,
    age: i32,
    height: f32,
}
impl User{
    fn display(&self,index:usize){
        match index{
            0 =>println!("Name: {}",self.name),
            1 =>println!("Age: {}",self.age),
            2 =>println!("Height: {}",self.height),
            _=>panic!("Fatal error"),
        }
    }
}

impl Display for (&str,i32,f32){
    fn display(&self,index:usize){
        match index{
            1=>println!("Name: {}",self.0),
            2=>println!("Age: {}",self.1),
            3=>println!("Height: {}",self.2),
            _=>panic!("Unknown index"),
        }
    }
}