fn hate_school(a: i32, b: i32) -> () {
    let result = a.pow(3) + b.pow(3) + 3 * a * b * (a + b);
    println!("{}",result)
}
//маркер что код не используется нигде
#[allow(dead_code)]
fn main(){
    let a =2;
    let b = 3;
    hate_school(a, b);
}

//test
#[cfg(test)]
mod tests{
    use super::*;
    
    #[test]
    fn test_hate_school(){
        hate_school(2, 2)
    }
}