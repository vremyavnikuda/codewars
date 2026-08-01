use std::collections::BTreeMap;

struct RangeModule {
    r: BTreeMap<i32, i32>,
}

impl RangeModule {
    fn new() -> Self {
        RangeModule { r: BTreeMap::new() }
    }

    fn add_range(&mut self, left: i32, right: i32) {
        let mut l = left;
        let mut r = right;

        let mut to_remove = Vec::new();

        for (&s, &e) in self.r.range(..=right) {
            if e < left {
                continue;
            }
            if s > right {
                break;
            }

            l = l.min(s);
            r = r.max(e);
            to_remove.push(s);
        }

        for k in to_remove {
            self.r.remove(&k);
        }

        self.r.insert(l, r);
    }

    fn query_range(&self, left: i32, right: i32) -> bool {
        if let Some((&s, &e)) = self.r.range(..=left).next_back() {
            e >= right
        } else {
            false
        }
    }

    fn remove_range(&mut self, left: i32, right: i32) {
        let mut to_add = Vec::new();
        let mut to_remove = Vec::new();

        for (&s, &e) in self.r.range(..right).rev() {
            if e <= left {
                break;
            }

            to_remove.push(s);

            if s < left {
                to_add.push((s, left));
            }
            if e > right {
                to_add.push((right, e));
            }
        }

        for k in to_remove {
            self.r.remove(&k);
        }

        for (s, e) in to_add {
            self.r.insert(s, e);
        }
    }
}

fn main() {
    let mut obj = RangeModule::new();
    obj.add_range(10, 20);
    obj.remove_range(14, 16);
    println!("queryRange(10, 14): {}", obj.query_range(10, 14));
    println!("queryRange(13, 15): {}", obj.query_range(13, 15));
    println!("queryRange(16, 17): {}", obj.query_range(16, 17));
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn t1() {
        let mut obj = RangeModule::new();
        obj.add_range(10, 20);
        obj.remove_range(14, 16);
        assert_eq!(obj.query_range(10, 14), true);
        assert_eq!(obj.query_range(13, 15), false);
        assert_eq!(obj.query_range(16, 17), true);
    }

    #[test]
    fn t2() {
        let mut obj = RangeModule::new();
        obj.add_range(10, 180);
        obj.add_range(150, 200);
        obj.add_range(250, 500);
        assert_eq!(obj.query_range(50, 100), true);
        assert_eq!(obj.query_range(180, 300), false);
        assert_eq!(obj.query_range(600, 1000), false);
        obj.remove_range(50, 150);
        assert_eq!(obj.query_range(50, 100), false);
    }

    #[test]
    fn t3() {
        let mut obj = RangeModule::new();
        obj.add_range(5, 8);
        assert_eq!(obj.query_range(3, 4), false);
        obj.remove_range(5, 6);
        obj.remove_range(3, 6);
        obj.add_range(1, 3);
        assert_eq!(obj.query_range(2, 3), true);
        obj.add_range(4, 8);
        assert_eq!(obj.query_range(2, 3), true);
        obj.remove_range(4, 9);
    }
}
