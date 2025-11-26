use std::collections::BTreeMap;

struct SummaryRanges {
    m: BTreeMap<i32, i32>,
}

impl SummaryRanges {
    fn new() -> Self {
        SummaryRanges { m: BTreeMap::new() }
    }

    fn add_num(&mut self, value: i32) {
        for (&s, &e) in self.m.iter() {
            if value >= s && value <= e {
                return;
            }
        }

        let mut s = value;
        let mut e = value;

        if let Some((&ps, &pe)) = self.m.range(..value).next_back() {
            if pe >= value - 1 {
                s = ps;
                e = e.max(pe);
                self.m.remove(&ps);
            }
        }

        if let Some((&ns, &ne)) = self.m.range(value..).next() {
            if ns <= value + 1 {
                e = ne;
                self.m.remove(&ns);
            }
        }

        self.m.insert(s, e);
    }

    fn get_intervals(&self) -> Vec<Vec<i32>> {
        self.m.iter().map(|(&s, &e)| vec![s, e]).collect()
    }
}

fn main() {
    let mut obj = SummaryRanges::new();
    obj.add_num(1);
    println!("{:?}", obj.get_intervals());
    obj.add_num(3);
    println!("{:?}", obj.get_intervals());
    obj.add_num(7);
    println!("{:?}", obj.get_intervals());
    obj.add_num(2);
    println!("{:?}", obj.get_intervals());
    obj.add_num(6);
    println!("{:?}", obj.get_intervals());
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn t1() {
        let mut obj = SummaryRanges::new();
        obj.add_num(1);
        assert_eq!(obj.get_intervals(), vec![vec![1, 1]]);
        obj.add_num(3);
        assert_eq!(obj.get_intervals(), vec![vec![1, 1], vec![3, 3]]);
        obj.add_num(7);
        assert_eq!(
            obj.get_intervals(),
            vec![vec![1, 1], vec![3, 3], vec![7, 7]]
        );
        obj.add_num(2);
        assert_eq!(obj.get_intervals(), vec![vec![1, 3], vec![7, 7]]);
        obj.add_num(6);
        assert_eq!(obj.get_intervals(), vec![vec![1, 3], vec![6, 7]]);
    }

    #[test]
    fn t2() {
        let mut obj = SummaryRanges::new();
        obj.add_num(1);
        obj.add_num(1);
        assert_eq!(obj.get_intervals(), vec![vec![1, 1]]);
    }

    #[test]
    fn t3() {
        let mut obj = SummaryRanges::new();
        obj.add_num(1);
        obj.add_num(3);
        obj.add_num(2);
        assert_eq!(obj.get_intervals(), vec![vec![1, 3]]);
    }
}
