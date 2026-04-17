pub struct Solution;

impl Solution{
    pub fn find_final_value(nums:Vec<i32>,mut original:i32)->i32{
        use std::cmp::Ordering::*;
        let mut z=nums;
        z.sort_unstable();
        let(mut i,n)=(0usize,z.len());
        while i<n{
            match unsafe{*z.get_unchecked(i)}.cmp(&original){
                Less=>i+=1,
                Equal=>{original<<=1;i+=1}
                Greater=>break,
            }
        }
        original
    }
}

#[cfg(test)]
mod tests{
    use super::Solution;

    #[test]
    fn t1(){assert_eq!(Solution::find_final_value(vec![5,3,6,1,12],3),24);}

    #[test]
    fn t2(){assert_eq!(Solution::find_final_value(vec![2,7,9],4),4);}

    #[test]
    fn t3(){assert_eq!(Solution::find_final_value(vec![1,2,2,4],1),8);}
}
