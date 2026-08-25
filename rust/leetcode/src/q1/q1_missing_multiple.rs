pub struct Solution;

impl Solution{
    pub fn missing_multiple(nums:Vec<i32>,k:i32)->i32{
        (1..).map(|q1|k*q1).find(|q2|!nums.contains(q2)).unwrap()
    }
}

#[cfg(test)]
mod tests{
    use super::Solution;

    #[test]
    fn t1(){assert_eq!(Solution::missing_multiple(vec![1,4,7,10,15],5),10);}

    #[test]
    fn t2(){assert_eq!(Solution::missing_multiple(vec![1,2,3],4),4);}

    #[test]
    fn t3(){assert_eq!(Solution::missing_multiple(vec![2,4,6,8],1),9);}
}
