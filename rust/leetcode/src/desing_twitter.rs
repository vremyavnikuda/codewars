use std::collections::{HashMap, HashSet};

struct Twitter {
    t: Vec<(i32, i32)>,
    f: HashMap<i32, HashSet<i32>>,
}

impl Twitter {
    fn new() -> Self {
        Twitter {
            t: Vec::new(),
            f: HashMap::new(),
        }
    }

    fn post_tweet(&mut self, user_id: i32, tweet_id: i32) {
        self.t.push((user_id, tweet_id));
    }

    fn get_news_feed(&self, user_id: i32) -> Vec<i32> {
        let mut r = Vec::new();

        for &(u, tid) in self.t.iter().rev() {
            if u == user_id || self.f.get(&user_id).map_or(false, |s| s.contains(&u)) {
                r.push(tid);
                if r.len() == 10 {
                    break;
                }
            }
        }

        r
    }

    fn follow(&mut self, follower_id: i32, followee_id: i32) {
        self.f
            .entry(follower_id)
            .or_insert_with(HashSet::new)
            .insert(followee_id);
    }

    fn unfollow(&mut self, follower_id: i32, followee_id: i32) {
        if let Some(s) = self.f.get_mut(&follower_id) {
            s.remove(&followee_id);
        }
    }
}

fn main() {
    let mut obj = Twitter::new();
    obj.post_tweet(1, 5);
    println!("getNewsFeed(1): {:?}", obj.get_news_feed(1));
    obj.follow(1, 2);
    obj.post_tweet(2, 6);
    println!("getNewsFeed(1): {:?}", obj.get_news_feed(1));
    obj.unfollow(1, 2);
    println!("getNewsFeed(1): {:?}", obj.get_news_feed(1));
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn t1() {
        let mut obj = Twitter::new();
        obj.post_tweet(1, 5);
        assert_eq!(obj.get_news_feed(1), vec![5]);
        obj.follow(1, 2);
        obj.post_tweet(2, 6);
        assert_eq!(obj.get_news_feed(1), vec![6, 5]);
        obj.unfollow(1, 2);
        assert_eq!(obj.get_news_feed(1), vec![5]);
    }

    #[test]
    fn t2() {
        let mut obj = Twitter::new();
        obj.post_tweet(1, 5);
        obj.post_tweet(2, 3);
        obj.post_tweet(1, 101);
        assert_eq!(obj.get_news_feed(1), vec![101, 5]);
    }

    #[test]
    fn t3() {
        let mut obj = Twitter::new();
        obj.post_tweet(1, 1);
        obj.follow(2, 1);
        assert_eq!(obj.get_news_feed(2), vec![1]);
        obj.unfollow(2, 1);
        assert_eq!(obj.get_news_feed(2), vec![]);
    }

    #[test]
    fn t4() {
        let mut obj = Twitter::new();
        for i in 0..15 {
            obj.post_tweet(1, i);
        }
        let feed = obj.get_news_feed(1);
        assert_eq!(feed.len(), 10);
        assert_eq!(feed[0], 14);
        assert_eq!(feed[9], 5);
    }
}
