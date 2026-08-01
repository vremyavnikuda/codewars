struct Solution;

impl Solution{
    #[inline(always)]
    pub fn min_mirror_pair_distance(nums:Vec<i32>)->i32{
        #[derive(Default)]
        struct _H(u64);
        impl std::hash::Hasher for _H{
            #[inline(always)]
            fn finish(&self)->u64{self.0}
            #[inline(always)]
            fn write(&mut self,b:&[u8]){
                let(mut z,mut i)=(0u64,0usize);
                while i<b.len(){z|=(b[i]as u64)<<((i&7)<<3);i+=1;}
                self.0=z;
            }
            #[inline(always)]
            fn write_i32(&mut self,i:i32){self.0=(i as u32)as u64;}
            #[inline(always)]
            fn write_u32(&mut self,i:u32){self.0=i as u64;}
        }
        type _S=std::hash::BuildHasherDefault<_H>;
        #[inline(always)]
        fn _r(mut x:i32)->i32{
            let mut y=0;
            while x>0{y=y*10+x%10;x/=10;}
            y
        }
        let n=nums.len();
        let(mut a,mut p,mut i)=((n as i32)+1,std::collections::HashMap::with_capacity_and_hasher(n,_S::default()),0usize);
        while i<n{
            let x=unsafe{*nums.get_unchecked(i)};
            if let Some(&j)=p.get(&x){
                let d=((i as u32).wrapping_sub(j))as i32;
                if d<a{
                    a=d;
                    if a==1{return 1;}
                }
            }
            p.insert(_r(x),i as u32);
            i+=1;
        }
        if a>n as i32{-1}else{a}
    }
}

#[cfg(test)]
mod tests{
    use super::Solution;

    #[test]
    fn t1(){assert_eq!(Solution::min_mirror_pair_distance(vec![21,12]),1);}

    #[test]
    fn t2(){assert_eq!(Solution::min_mirror_pair_distance(vec![12,1,21,12]),1);}

    #[test]
    fn t3(){assert_eq!(Solution::min_mirror_pair_distance(vec![1,2,3,4]),-1);}

    #[test]
    fn t4(){assert_eq!(Solution::min_mirror_pair_distance(vec![12,34,21,43]),2);}
}
