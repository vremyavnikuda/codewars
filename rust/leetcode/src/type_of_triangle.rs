pub struct Solution;

impl Solution {
    pub fn triangle_type(nums: Vec<i32>) -> String {
        let (a, b, c) = (nums[0], nums[1], nums[2]);
        
        if a + b <= c || a + c <= b || b + c <= a {
            return "none".to_string();
        }
        
        if a == b && b == c {
            "equilateral".to_string()
        } else if a == b || b == c || a == c {
            "isosceles".to_string()
        } else {
            "scalene".to_string()
        }
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_example_1() {
        assert_eq!(Solution::triangle_type(vec![3, 3, 3]), "equilateral");
    }

    #[test]
    fn test_example_2() {
        assert_eq!(Solution::triangle_type(vec![3, 4, 5]), "scalene");
    }

    #[test]
    fn test_isosceles_1() {
        assert_eq!(Solution::triangle_type(vec![5, 5, 3]), "isosceles");
    }

    #[test]
    fn test_isosceles_2() {
        assert_eq!(Solution::triangle_type(vec![3, 5, 5]), "isosceles");
    }

    #[test]
    fn test_isosceles_3() {
        assert_eq!(Solution::triangle_type(vec![5, 3, 5]), "isosceles");
    }

    #[test]
    fn test_none_sum_equals() {
        assert_eq!(Solution::triangle_type(vec![1, 2, 3]), "none");
    }

    #[test]
    fn test_none_sum_less() {
        assert_eq!(Solution::triangle_type(vec![1, 2, 10]), "none");
    }

    #[test]
    fn test_scalene_various() {
        assert_eq!(Solution::triangle_type(vec![2, 3, 4]), "scalene");
        assert_eq!(Solution::triangle_type(vec![7, 8, 9]), "scalene");
    }

    #[test]
    fn test_minimal_triangle() {
        assert_eq!(Solution::triangle_type(vec![1, 1, 1]), "equilateral");
    }

    #[test]
    fn test_large_values() {
        assert_eq!(Solution::triangle_type(vec![100, 100, 100]), "equilateral");
        assert_eq!(Solution::triangle_type(vec![99, 100, 100]), "isosceles");
        assert_eq!(Solution::triangle_type(vec![98, 99, 100]), "scalene");
    }

    #[test]
    fn test_edge_case_valid() {
        assert_eq!(Solution::triangle_type(vec![2, 2, 3]), "isosceles");
    }

    #[test]
    fn test_edge_case_invalid() {
        assert_eq!(Solution::triangle_type(vec![1, 1, 2]), "none");
    }
}
