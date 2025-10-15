pub struct Solution;

impl Solution {
    pub fn longest_balanced(s: String) -> i32 {
        let b = s.as_bytes();
        let n = b.len();
        let mut max_len = 0;
        
        for i in 0..n {
            let mut cnt = [0; 3];
            
            for j in i..n {
                cnt[(b[j] - b'a') as usize] += 1;
                
                let mut freq = 0;
                let mut balanced = true;
                
                for &c in &cnt {
                    if c > 0 {
                        if freq == 0 {
                            freq = c;
                        } else if c != freq {
                            balanced = false;
                            break;
                        }
                    }
                }
                
                if balanced {
                    max_len = max_len.max(j - i + 1);
                }
            }
        }
        
        max_len as i32
    }
}
