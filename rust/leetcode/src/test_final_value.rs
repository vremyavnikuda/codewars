pub mod final_value_after_operations {
    pub struct Solution;

    impl Solution {
        pub fn final_value_after_operations(operations: Vec<String>) -> i32 {
            let mut x = 0;
            
            for op in operations {
                // Check the middle character to determine increment or decrement
                if op.chars().nth(1).unwrap() == '+' {
                    x += 1;
                } else {
                    x -= 1;
                }
            }
            
            x
        }
    }
}

#[cfg(test)]
mod tests {
    use crate::test_final_value::final_value_after_operations::Solution;

    #[test]
    fn test_final_value_after_operations() {
        // Example 1
        let operations1 = vec!["--X".to_string(), "X++".to_string(), "X++".to_string()];
        assert_eq!(Solution::final_value_after_operations(operations1), 1);

        // Example 2
        let operations2 = vec!["++X".to_string(), "++X".to_string(), "X++".to_string()];
        assert_eq!(Solution::final_value_after_operations(operations2), 3);

        // Example 3
        let operations3 = vec!["X++".to_string(), "++X".to_string(), "--X".to_string(), "X--".to_string()];
        assert_eq!(Solution::final_value_after_operations(operations3), 0);
    }
}

fn main() {
    // Example usage
    let operations1 = vec!["--X".to_string(), "X++".to_string(), "X++".to_string()];
    println!("Result 1: {}", Solution::final_value_after_operations(operations1)); // Should print 1
    
    let operations2 = vec!["++X".to_string(), "++X".to_string(), "X++".to_string()];
    println!("Result 2: {}", Solution::final_value_after_operations(operations2)); // Should print 3
    
    let operations3 = vec!["X++".to_string(), "++X".to_string(), "--X".to_string(), "X--".to_string()];
    println!("Result 3: {}", Solution::final_value_after_operations(operations3)); // Should print 0
}