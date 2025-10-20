pub struct Solution;

impl Solution {
    pub fn final_value_after_operations(operations: Vec<String>) -> i32 {
        let mut x = 0;
        
        for op in operations {
            if op.chars().nth(1).unwrap() == '+' {
                x += 1;
            } else {
                x -= 1;
            }
        }
        
        x
    }
}