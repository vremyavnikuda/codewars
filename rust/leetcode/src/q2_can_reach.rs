pub struct Solution;

impl Solution {
    #[inline(always)]
    pub fn can_reach(mut arr: Vec<i32>, start: i32) -> bool {
        let (n, mut q) = (arr.len(), Vec::<usize>::with_capacity(arr.len()));
        unsafe {
            let p = arr.as_mut_ptr();
            let s = start as usize;
            *p.add(s) = !*p.add(s);
            q.push(s);
            while let Some(i) = q.pop() {
                let d = !*p.add(i);
                if d == 0 {
                    return true;
                }
                let j = d as usize;
                let r = i + j;
                if r < n && *p.add(r) >= 0 {
                    *p.add(r) = !*p.add(r);
                    q.push(r);
                }
                let l = i.wrapping_sub(j);
                if l < n && *p.add(l) >= 0 {
                    *p.add(l) = !*p.add(l);
                    q.push(l);
                }
            }
        }
        false
    }
}

#[cfg(test)]
mod tests {
    use super::Solution;

    #[test]
    fn t1() {
        assert!(Solution::can_reach(vec![4, 2, 3, 0, 3, 1, 2], 5));
    }

    #[test]
    fn t2() {
        assert!(Solution::can_reach(vec![4, 2, 3, 0, 3, 1, 2], 0));
    }

    #[test]
    fn t3() {
        assert!(!Solution::can_reach(vec![3, 0, 2, 1, 2], 2));
    }
}
