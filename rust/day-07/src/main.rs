#![allow(unused)]
fn main() {}

#[derive(Debug)]
struct Node {
    up: Option<Box<Node>>,
    children: Vec<Option<Box<Node>>>,
    name: String,
    val: u32,
    is_dir: bool,
}

fn dfs(curr: Box<Node>, mut final_ans: &u32) -> u32 {
    let mut ans: u32 = curr.val;
    for child in curr.children {
        if let v = child.unwrap() {
            ans += dfs(v, final_ans);
        }
    }
    dbg!(&curr.name, ans);
    // if curr.is_dir && ans <= 100000 {
    //     *final_ans += ans;
    // }
    ans
}

fn solve_part1(input: &str) -> u32 {
    let mut head: Box<Node> = Box::new(Node {
        up: None,
        children: Vec::new(),
        name: String::from("/"),
        val: 0,
        is_dir: true,
    });

    let start = head;

    for line in input.lines() {
        // is a command
        if line.starts_with('$') {
            let line: Vec<&str> = line.split(' ').collect();
            // dbg!(&line);
            match line[1] {
                "cd" => {
                    let dir_name = line[2].to_string();
                    if dir_name == "/" {
                    } else if dir_name == ".." {
                        head = head.up.unwrap();
                    } else {
                        let mut found = false;
                        // dbg!(&head);
                        // assert!(&head.children.len() > &0);
                        for child in &head.children {
                            // very bad implementation, will improve later?
                            // not sure if this is still going to work or not?
                            // dbg!(&child);
                            if *child.unwrap().name == dir_name {
                                head = child.unwrap();
                                found = true;
                                break;
                            }
                        }
                        assert!(found);
                    }
                }
                "ls" => {
                    // do nothing?
                }
                _ => panic!(),
            }
        } else {
            let line: Vec<&str> = line.split(' ').collect();
            match line[0] {
                "dir" => {
                    let dir_name = line[1];
                    let add = Node {
                        up: Some(head),
                        children: Vec::new(),
                        name: String::from(dir_name),
                        val: 0,
                        is_dir: true,
                    };
                    head.children.push(Some(Box::new(add)));
                    dbg!("pushed into ", &head);
                }
                _ => {
                    let file_size: u32 = line[0].parse().unwrap();
                    let file_name = line[1];
                    let add = Node {
                        up: Some(head),
                        children: Vec::new(),
                        name: String::from(file_name),
                        val: file_size,
                        is_dir: false,
                    };
                    head.children.push(Some(Box::new(add)));
                    dbg!("pushed into ", &head);
                }
            }
        }
    }
    let mut final_ans = 0;
    dfs(start, &final_ans);
    final_ans
}

fn solve_part2(input: &str) -> u32 {
    0
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn samples_part1() {
        let input = include_str!("../data/sample.txt");
        assert_eq!(solve_part1(input), 95437);
    }

    // #[test]
    fn samples_part2() {
        let input = include_str!("../data/sample.txt");
        assert_eq!(solve_part2(input), 24933642);
    }

    // #[test]
    fn part1() {
        let input = include_str!("../data/input.txt");
        assert_eq!(solve_part1(input), 1428881);
    }

    // #[test]
    fn part2() {
        let input = include_str!("../data/input.txt");
        assert_eq!(solve_part2(input), 10475598);
    }
}
