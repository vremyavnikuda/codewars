struct SubrectangleQueries {
    g: Vec<Vec<i32>>,
    u: Vec<(i32, i32, i32, i32, i32)>,
}

impl SubrectangleQueries {
    fn new(rectangle: Vec<Vec<i32>>) -> Self {
        SubrectangleQueries {
            g: rectangle,
            u: Vec::new(),
        }
    }

    fn update_subrectangle(&mut self, row1: i32, col1: i32, row2: i32, col2: i32, new_value: i32) {
        self.u.push((row1, col1, row2, col2, new_value));
    }

    fn get_value(&self, row: i32, col: i32) -> i32 {
        for &(r1, c1, r2, c2, v) in self.u.iter().rev() {
            if row >= r1 && row <= r2 && col >= c1 && col <= c2 {
                return v;
            }
        }
        self.g[row as usize][col as usize]
    }
}

fn main() {
    let mut obj = SubrectangleQueries::new(vec![
        vec![1, 2, 1],
        vec![4, 3, 4],
        vec![3, 2, 1],
        vec![1, 1, 1],
    ]);

    println!("getValue(0, 2): {}", obj.get_value(0, 2));
    obj.update_subrectangle(0, 0, 3, 2, 5);
    println!("getValue(0, 2): {}", obj.get_value(0, 2));
    println!("getValue(3, 1): {}", obj.get_value(3, 1));
    obj.update_subrectangle(3, 0, 3, 2, 10);
    println!("getValue(3, 1): {}", obj.get_value(3, 1));
    println!("getValue(0, 2): {}", obj.get_value(0, 2));
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn t1() {
        let mut obj = SubrectangleQueries::new(vec![
            vec![1, 2, 1],
            vec![4, 3, 4],
            vec![3, 2, 1],
            vec![1, 1, 1],
        ]);

        assert_eq!(obj.get_value(0, 2), 1);
        obj.update_subrectangle(0, 0, 3, 2, 5);
        assert_eq!(obj.get_value(0, 2), 5);
        assert_eq!(obj.get_value(3, 1), 5);
        obj.update_subrectangle(3, 0, 3, 2, 10);
        assert_eq!(obj.get_value(3, 1), 10);
        assert_eq!(obj.get_value(0, 2), 5);
    }

    #[test]
    fn t2() {
        let mut obj = SubrectangleQueries::new(vec![vec![1, 1, 1], vec![2, 2, 2], vec![3, 3, 3]]);

        assert_eq!(obj.get_value(0, 0), 1);
        obj.update_subrectangle(0, 0, 2, 2, 100);
        assert_eq!(obj.get_value(0, 0), 100);
        assert_eq!(obj.get_value(2, 2), 100);
        obj.update_subrectangle(1, 1, 2, 2, 20);
        assert_eq!(obj.get_value(2, 2), 20);
    }

    #[test]
    fn t3() {
        let mut obj = SubrectangleQueries::new(vec![vec![1, 2, 3], vec![4, 5, 6], vec![7, 8, 9]]);

        assert_eq!(obj.get_value(1, 1), 5);
        obj.update_subrectangle(0, 0, 0, 0, 99);
        assert_eq!(obj.get_value(0, 0), 99);
        assert_eq!(obj.get_value(1, 1), 5);
        obj.update_subrectangle(1, 1, 1, 1, 77);
        assert_eq!(obj.get_value(1, 1), 77);
    }
}
