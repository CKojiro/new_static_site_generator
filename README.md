# Static Site Generator

A static site generator written in C++17 from scratch using only the C++ standard library.

## Motivation

I needed a place to showcase my projects as a developer. So my first thought was "make a website", however I have very little experience with front-end development so that was quickly ruled out. I then thought, I have previously done a static site generator project in Python, so how hard could it be to develop in my most proficient coding language? It turns out, quite a bit harder, but not impossible.

## Technical Challenges

I did not want to use a pre-existing library in order to make this trivial. I wanted to develop this from scratch in order to showcase my ability. So I only used headers from the standard library. The parsing logic and generation is all custom.

Some of the key areas I worked on include:

- Object-oriented design and polymorphic HTML nodes
- Markdown parsing and conversion to HTML
- String processing and regular expressions
- Recursive filesystem traversal and page generation
- HTML templating and placeholder replacement
- Configurable basepaths for deployment on Github Pages

## Technologies

- C++17
- CMake

## Build

```
cmake -S . -B build
cmake --build build
```

## Usage

I have included a build script that takes care of the cmake build and runs main. Just run it with
```
./build.sh
```

## Conclusion

This project became more than a way to create my portfolio. It was an opportunity to revisit a familiar problem, solve it in C++, and build a tool that I now use to showcase my work.

Check out the portfolio here:

[Portfolio](https://CKojiro.github.io/new_static_site_generator/)