#![allow(unused)]
fn main() {}

#[derive(Debug, Clone, PartialEq)]
enum NodeType {
    DIRECTORY,
    FILE,
}

#[derive(Debug, Clone)]
struct Node {
    name: String,
    value: u32,
    node_type: NodeType,
    id: usize,
}

#[derive(Debug, Clone)]
struct GNode {
    name: String,
    value: u32,
    node_type: NodeType,
    id: usize,
}

fn dfs_part1(node: GNode, graph: &Vec<Vec<GNode>>, values: &Vec<u32>, answer: &mut u32) -> u32 {
    let mut total = values[node.id];
    for child in &graph[node.id] {
        total += dfs_part1(child.clone(), graph, values, answer);
    }
    if node.node_type == NodeType::DIRECTORY {
        if total <= 100_000 {
            *answer += total;
        }
    }
    total
}

fn dfs_part2(
    node: GNode,
    graph: &Vec<Vec<GNode>>,
    values: &Vec<u32>,
    dir_sizes: &mut Vec<u32>,
) -> u32 {
    let mut total = values[node.id];
    for child in &graph[node.id] {
        total += dfs_part2(child.clone(), graph, values, dir_sizes);
    }
    if node.node_type == NodeType::DIRECTORY {
        dir_sizes.push(total);
    }
    total
}

fn solve_part1(input: &str) -> u32 {
    let mut dir_tree: Vec<Node> = vec![];
    let mut graph: Vec<Vec<GNode>> = Vec::new();
    let mut values = vec![0u32; 10000];
    for _ in 0..10000 {
        graph.push(Vec::new());
    }
    let mut id = 0;

    for line in input.lines() {
        let tokens: Vec<&str> = line.split(' ').collect();
        match tokens[..] {
            ["$", "cd", dir_name] => match dir_name {
                ".." => {
                    dir_tree.pop();
                }
                "/" => dir_tree.push(Node {
                    name: "/".to_string(),
                    value: 0,
                    node_type: NodeType::DIRECTORY,
                    id: 0,
                }),
                dir_name => {
                    let parent = dir_tree.last().unwrap().id;
                    let mut nid = 0;
                    for child in &graph[parent] {
                        if child.name == dir_name {
                            nid = child.id;
                            break;
                        }
                    }

                    dir_tree.push(Node {
                        name: dir_name.to_string(),
                        value: 0,
                        node_type: NodeType::DIRECTORY,
                        id: nid,
                    })
                }
            },
            ["$", "ls"] => {}
            ["dir", dir_name] => {
                let parent = dir_tree.last().unwrap().id;
                id += 1;
                graph[parent].push(GNode {
                    name: dir_name.to_string(),
                    value: 0,
                    node_type: NodeType::DIRECTORY,
                    id,
                });
            }
            [file_size, file_name] => {
                let parent = dir_tree.last().unwrap().id;
                id += 1;
                graph[parent].push(GNode {
                    name: file_name.to_string(),
                    value: file_size.parse().unwrap(),
                    node_type: NodeType::FILE,
                    id,
                });
                values[id] = file_size.parse().unwrap();
            }
            _ => panic!(),
        }
    }

    let mut answer = 0;
    dfs_part1(
        GNode {
            name: "/".to_string(),
            value: 0,
            node_type: NodeType::DIRECTORY,
            id: 0,
        },
        &graph,
        &values,
        &mut answer,
    );
    answer
}

fn solve_part2(input: &str) -> u32 {
    let mut dir_tree: Vec<Node> = vec![];
    let mut graph: Vec<Vec<GNode>> = Vec::new();
    let mut values = vec![0u32; 10000];
    for _ in 0..10000 {
        graph.push(Vec::new());
    }
    let mut id = 0;

    for line in input.lines() {
        let tokens: Vec<&str> = line.split(' ').collect();
        match tokens[..] {
            ["$", "cd", dir_name] => match dir_name {
                ".." => {
                    dir_tree.pop();
                }
                "/" => dir_tree.push(Node {
                    name: "/".to_string(),
                    value: 0,
                    node_type: NodeType::DIRECTORY,
                    id: 0,
                }),
                dir_name => {
                    let parent = dir_tree.last().unwrap().id;
                    let mut nid = 0;
                    for child in &graph[parent] {
                        if child.name == dir_name {
                            nid = child.id;
                            break;
                        }
                    }

                    dir_tree.push(Node {
                        name: dir_name.to_string(),
                        value: 0,
                        node_type: NodeType::DIRECTORY,
                        id: nid,
                    })
                }
            },
            ["$", "ls"] => {}
            ["dir", dir_name] => {
                let parent = dir_tree.last().unwrap().id;
                id += 1;
                graph[parent].push(GNode {
                    name: dir_name.to_string(),
                    value: 0,
                    node_type: NodeType::DIRECTORY,
                    id,
                });
            }
            [file_size, file_name] => {
                let parent = dir_tree.last().unwrap().id;
                id += 1;
                graph[parent].push(GNode {
                    name: file_name.to_string(),
                    value: file_size.parse().unwrap(),
                    node_type: NodeType::FILE,
                    id,
                });
                values[id] = file_size.parse().unwrap();
            }
            _ => panic!(),
        }
    }

    let mut dir_sizes: Vec<u32> = Vec::new();
    dfs_part2(
        GNode {
            name: "/".to_string(),
            value: 0,
            node_type: NodeType::DIRECTORY,
            id: 0,
        },
        &graph,
        &values,
        &mut dir_sizes,
    );
    // size of home directory
    let all: u32 = *dir_sizes.iter().max().unwrap();
    let req = 300_00_000 - (700_00_000 - all);

    dir_sizes
        .into_iter()
        .filter(|size| size >= &req)
        .min()
        .unwrap()
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn samples_part1() {
        let input = include_str!("../data/sample.txt");
        assert_eq!(solve_part1(input), 95437);
    }

    #[test]
    fn samples_part2() {
        let input = include_str!("../data/sample.txt");
        assert_eq!(solve_part2(input), 24933642);
    }

    #[test]
    fn part1() {
        let input = include_str!("../data/input.txt");
        assert_eq!(solve_part1(input), 1428881);
    }

    #[test]
    fn part2() {
        let input = include_str!("../data/input.txt");
        assert_eq!(solve_part2(input), 10475598);
    }
}
