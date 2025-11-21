#!/usr/bin/env rust-script

use std::collections::HashMap;
pub struct Solution;
impl Solution {
    pub fn find_itinerary(tickets: Vec<Vec<String>>) -> Vec<String> {
        let mut graph: HashMap<String, Vec<String>> = HashMap::new();

        for ticket in &tickets {
            let from = &ticket[0];
            let to = &ticket[1];
            graph.entry(from.clone()).or_insert_with(Vec::new).push(to.clone());
        }

        for destinations in graph.values_mut() {
            destinations.sort();
        }

        let mut route = Vec::new();
        let mut stack = vec!["JFK".to_string()];

        while let Some(airport) = stack.last().cloned() {
            if let Some(destinations) = graph.get_mut(&airport) {
                if !destinations.is_empty() {
                    let next = destinations.remove(0);
                    stack.push(next);
                } else {
                    route.push(stack.pop().unwrap());
                }
            } else {
                route.push(stack.pop().unwrap());
            }
        }

        route.reverse();
        route
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_example_1() {
        let tickets = vec![
            vec!["MUC".to_string(), "LHR".to_string()],
            vec!["JFK".to_string(), "MUC".to_string()],
            vec!["SFO".to_string(), "SJC".to_string()],
            vec!["LHR".to_string(), "SFO".to_string()]
        ];
        let result = Solution::find_itinerary(tickets);
        assert_eq!(result, vec!["JFK", "MUC", "LHR", "SFO", "SJC"]);
    }

    #[test]
    fn test_example_2() {
        let tickets = vec![
            vec!["JFK".to_string(), "SFO".to_string()],
            vec!["JFK".to_string(), "ATL".to_string()],
            vec!["SFO".to_string(), "ATL".to_string()],
            vec!["ATL".to_string(), "JFK".to_string()],
            vec!["ATL".to_string(), "SFO".to_string()]
        ];
        let result = Solution::find_itinerary(tickets);
        assert_eq!(result, vec!["JFK", "ATL", "JFK", "SFO", "ATL", "SFO"]);
    }
}

fn main() {
    let tickets = vec![
        vec!["MUC".to_string(), "LHR".to_string()],
        vec!["JFK".to_string(), "MUC".to_string()],
        vec!["SFO".to_string(), "SJC".to_string()],
        vec!["LHR".to_string(), "SFO".to_string()]
    ];
    println!("Input: {:?}", tickets);
    println!("Result: {:?}", Solution::find_itinerary(tickets));
}
