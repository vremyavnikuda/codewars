use std::collections::HashMap;

struct RangeFreqQuery {
    m: HashMap<i32, Vec<usize>>,
}

impl RangeFreqQuery {
    fn new(arr: Vec<i32>) -> Self {
        let mut m = HashMap::new();

        for (i, &v) in arr.iter().enumerate() {
            m.entry(v).or_insert_with(Vec::new).push(i);
        }

        RangeFreqQuery { m }
    }

    fn query(&self, left: i32, right: i32, value: i32) -> i32 {
        if let Some(p) = self.m.get(&value) {
            let l = left as usize;
            let r = right as usize;

            let s = p.binary_search(&l).unwrap_or_else(|x| x);
            let e = p.binary_search(&(r + 1)).unwrap_or_else(|x| x);

            (e - s) as i32
        } else {
            0
        }
    }
}

fn main() {
    let obj = RangeFreqQuery::new(vec![12, 33, 4, 56, 22, 2, 34, 33, 22, 12, 34, 56]);
    println!("query(1, 2, 4): {}", obj.query(1, 2, 4));
    println!("query(0, 11, 33): {}", obj.query(0, 11, 33));
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn t1() {
        let obj = RangeFreqQuery::new(vec![12, 33, 4, 56, 22, 2, 34, 33, 22, 12, 34, 56]);
        assert_eq!(obj.query(1, 2, 4), 1);
        assert_eq!(obj.query(0, 11, 33), 2);
    }

    #[test]
    fn t2() {
        let obj = RangeFreqQuery::new(vec![1, 1, 1, 1, 1]);
        assert_eq!(obj.query(0, 4, 1), 5);
        assert_eq!(obj.query(1, 3, 1), 3);
        assert_eq!(obj.query(0, 0, 1), 1);
    }

    #[test]
    fn t3() {
        let obj = RangeFreqQuery::new(vec![1, 2, 3, 4, 5]);
        assert_eq!(obj.query(0, 4, 1), 1);
        assert_eq!(obj.query(0, 4, 6), 0);
        assert_eq!(obj.query(2, 4, 3), 1);
    }

    #[test]
    fn t4() {
        let obj = RangeFreqQuery::new(vec![5, 5, 1, 3, 5, 2, 5]);
        assert_eq!(obj.query(0, 6, 5), 4);
        assert_eq!(obj.query(1, 4, 5), 2);
        assert_eq!(obj.query(3, 5, 5), 1);
    }
}
