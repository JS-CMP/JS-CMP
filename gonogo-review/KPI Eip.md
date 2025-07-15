---
title: KPI Eip

---

# EIP Support Guide Technical Track
## Introduction

Welcome to the guide designed to support you throughout the Technical Track of the Epitech Innovative Project (EIP). This track allows you to explore and integrate advanced technologies, tackle complex technical challenges, and demonstrate in depth expertise in a specific technological field.

## Mandatory Objectives

### Evaluating and Integrating New Technologies

#### Regular Technology Watch

As part of our commitment to staying up to date with modern C++ standards, we continuously integrated and experimented with recent language features relevant to the JS-CMP project.

##### **`std::variant` / `std::optional` (C++17)**

These features are at the core of our project architecture. `std::variant` allows us to represent JavaScript’s dynamic typing within C++ by storing values of multiple possible types in a single variable. Combined with `std::optional`, we handle undefined or nullable values gracefully, closely mimicking JavaScript semantics.

##### **`<stacktrace>` (C++23)**

Used to provide meaningful runtime error reporting, this feature is central to our exception system. It helps us link C++ exceptions back to their original JavaScript source locations using source maps, improving debugging and developer feedback.

By following the evolution of the C++ standard and consulting technical blogs, proposal discussions (e.g., on [wg21.link](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2023/n4950.pdf)), and library documentation, we ensured that JS-CMP stays modern, robust, and aligned with best practices.


#### Research Documentation

##### **Benchmarks**

We conducted benchmarks to compare the performance of different C++ constructs and data structures relevant to our transpilation engine:

* `std::string` vs custom **Rope** implementation: to evaluate efficient string concatenation strategies for large, mutable JavaScript strings.
* `std::visit`: assessed in the context of our variant based AST and runtime type dispatching.

![Benchmark](https://hackmd.io/_uploads/HkJxp8KQxg.png)

##### **Key Articles and References Consulted**

Articles:
* [How is async/await transpiled to ES5?](https://cmichel.io/how-is-async-await-transpiled-to-es5)
* [Using ES6 generators and `yield` for async workflows](https://www.bennadel.com/blog/3123-using-es6-generators-and-yield-to-implement-asynchronous-workflows-in-javascript.htm)
* [Ropes: an Alternative to Strings - Paper](https://www.cs.tufts.edu/comp/150FP/archive/hans-boehm/ropes.pdf)
* [NodeJS documentation](https://nodejs.org/api/documentation.html#about-this-documentation)
* [ECMA script specification](https://262.ecma-international.org)
* [V8 documentation](https://v8docs.nodesource.com/node-24.1/)
* [Profiler documentation](https://www.jetbrains.com/help/clion/cpu-profiler.html#macos)

Github:
* [IdOp: custom operator in C++](https://github.com/cogwheel/IdOp)
* [Are We Fast Yet? – JS performance across runtimes](https://github.com/smarr/are-we-fast-yet)
* [JS tester](https://github.com/tc39/test262)

Youtube:

* [Modern C++ Techniques](https://www.youtube.com/watch?v=ZQFzMfHIxng)
* [Behind the scenes of JS engines](https://www.youtube.com/watch?v=EmzdmqUWq3o)
* [LLVM optimization insights](https://www.youtube.com/watch?v=hp4Nlf8IRgs)
* [Web browser from scratch devlogs](https://www.youtube.com/@LadybirdBrowser)
* [JS Engine explained](https://www.youtube.com/watch?v=xckH5s3UuX4)
* [Fast JS](https://www.youtube.com/watch?v=_pWA4rbzvIg)
* [Advanced C++ technique](https://www.youtube.com/watch?v=JkLZrV-7m9w&list=PL71Y0EmrppR0KyZvQWj63040UEzKQU7n8&index=7)
* [C++ variant](https://www.youtube.com/watch?v=qCc_Vqg3hJk)

These resources helped us understand how modern JS runtimes work internally, how asynchronous control flow can be lowered to simpler constructs, and how C++ can be used effectively to replicate similar patterns.

#### Practical Application of New Technologies

Throughout the JS-CMP project, we regularly explored and tested new technologies by developing various Proofs of Concept (POCs) and experimental modules. These experiments allowed us to evaluate libraries, compiler features, and language capabilities relevant to our transpiler.

##### **Examples of Technologies Explored**

* **Build Ninja** – Tested as a lightweight and fast alternative build system.
* **`<stacktrace>`** – Explored C++23’s built in stack trace capabilities for improving debug information during transpilation.
![image](https://hackmd.io/_uploads/H1gWBLHrlx.png)
* **ECMA Compliant Object Model** – Designed a prototype for an object structure closely matching JavaScript’s dynamic object behavior in C++. This experiment can be see [here](https://github.com/JS-CMP/JS-CMP/tree/wip/Object)


* **Boost ArgPars** – Experimented with Boost’s argument parsing utilities to handle CLI interactions for the transpiler.
![image](https://hackmd.io/_uploads/Hk-0VIrHel.png)

All experiments and documentation have been maintained in a private repository:

**Private Repository**: [JS-CMP/POC](https://github.com/JS-CMP/POC)

These POCs demonstrate our hands on engagement with modern tools and techniques, and our ability to critically assess their relevance for the JS-CMP toolchain.


#### Engagement in Tech Communities

LibrOpen is a solution project made by epitech student for the EIP to find and list all the open source project.

We have setup our project on the website to be found by developpers and users around the world.

The project can be seen [here](https://libropen.com/en/projects/js-cmp).

![Screenshot 2025-06-18 at 10-49-38 KPI Eip - HackMD](https://hackmd.io/_uploads/HkMaoWgVlg.png)

We have also post our project on the c++ discord. And we receive question and remark about our project.

The discussion can be seen [here](https://discord.com/channels/1130464154344493166/1384848555143069777)

we have made a reddit post. we did get a lot's of comment. You can see it [here](https://www.reddit.com/r/cpp/comments/1ledk6x/project_jscmp_a_javascripttoc_transpiler_feedback/?sort=new)

![image](https://hackmd.io/_uploads/BkdtKP-Hge.png)

And we have also made a dev.to post but we didn't get any comment on it. It can be seen [here](https://dev.to/victornu/project-js-cmp-a-javascript-to-c-transpiler-feedback-welcome-23o3)

![image](https://hackmd.io/_uploads/SkcwdDWrel.png)


## Complementary Objectives

### B - Developing Community Contributions

#### Clear Licensing Position

We chose the **GNU General Public License v3 (GPLv3)** for JS-CMP to ensure that the project remains free and open-source, and that any derivative works also stay open and accessible to the community. The GPLv3 enforces a strong copyleft model, meaning any modified versions must also be released under the same license. This fosters a collaborative environment and encourages contributions from developers who share similar free software values.

##### **Why GPLv3?**

Our goal with JS-CMP is not only to provide a powerful JavaScript to C++ transpiler, but also to protect the freedom of its users. By choosing GPLv3, we guarantee that improvements and extensions to the project remain available to everyone, which aligns with our commitment to open development and long-term transparency.

##### **Advantages**

* Strong user freedom protection
* Ensures derivative works remain open source (strong copyleft)
* Widely used and supported by the open source community

##### **Disadvantages**

* Incompatible with certain proprietary licenses
* Stricter legal obligations for redistribution
* Potentially less appealing for commercial adoption

##### **Notable Projects Using GPLv3**

* GNU/Linux
* VLC media player
* WordPress
* GCC (GNU Compiler Collection)

#### Engaging Developer Communities

We have setup a website to find contributor and make people interested in our project. you can find our github [here](https://github.com/JS-CMP/web) and the website url [here](https://js-cmp.github.io/web/). We have also setup a plausible on the website to analysis the trafic on it. The website is SSR to make the SEO better and rank up on the article.

![image](https://hackmd.io/_uploads/HyQYS8SSll.png)


We have made 2 article about our open source project.
- [Reducing Boilerplate in C++ with Macros](https://js-cmp.github.io/web/blog/1)
![Screenshot 2025-07-04 at 15.24.26-min](https://hackmd.io/_uploads/SJ_LIIHree.png)

- [Optimizing string concatenation in C++ with Rope data strucuture](https://js-cmp.github.io/web/blog/2)
![Screenshot 2025-07-04 at 15.25.03-min](https://hackmd.io/_uploads/SkUPLUSBex.png)

Plausible:

![image](https://hackmd.io/_uploads/BJJEuObrle.png)


We can see after the post on all the socials. We had a big bump on the trafic of the github main repo

![image](https://hackmd.io/_uploads/HJj6SdZHgx.png)


To maximize the number of contributors we had all community standards:

![image](https://hackmd.io/_uploads/B1fSL_WSee.png)

as you can see we have added all the template needed for pull request and issue. We have also added a security policy.

#### Documenting Contributions

We made concrete contributions to open source projects as part of our technical watch and active involvement in developer communities.

##### Contribution to **Bun**

We submitted a pull request to fix an issue in Bun’s SQLite interface where the `.all()` method did not return an array as expected:

* **PR**: [fix(sqlite) Insert .all() does not return an array – #5946](https://github.com/oven-sh/bun/pull/5946)

![Screenshot 2025-07-04 at 15.27.41](https://hackmd.io/_uploads/BkM1PLrSel.png)


We chose to contribute to Bun because it is a high performance JavaScript runtime, much like our own project, JS-CMP. By diving into its source code, we gained insight into how a modern JS runtime handles native bindings, database drivers, and type consistency—knowledge that directly informs the design and implementation of our transpiler.


We’ve also built a C++ library for custom operators, which is a core dependency of [JS-CMP](https://github.com/JS-CMP/JS-CMP). You can check it out [here](https://github.com/SimonBandiera/SyntaxSmith). This library extends C++ syntax capabilities to support JavaScript  like operator behavior and is essential for accurate transpilation. As it's part of the open source stack, we actively welcome contributions whether you're fixing bugs, improving performance, or proposing new operator features.

![Screenshot 2025-07-04 at 15.28.45](https://hackmd.io/_uploads/S1V7DISSgl.png)





### C - Collaborating with Technical Experts

#### Identifying the Right Technical Problem Solvers

We have found 3 experts and PhD researchers in Computer Science at the University of Kent specialists in C++, transpilation, and programming language theory and invited them to review our project:

1. **[Mark Batty](https://www.kent.ac.uk/school-of-computing/people/3126/batty-mark)**
   A Professor in Concurrency Semantics, he develops rigorous mathematical models and formal verification techniques for real world concurrent systems, particularly focusing on C/C++ memory models and compiler/hardware interactions.
![Screenshot 2025-07-04 at 15.34.03](https://hackmd.io/_uploads/ByQHYUBrxx.png)

2. **[Michael Vollmer](https://www.kent.ac.uk/school-of-computing/people/4728/vollmer-michael)**
   A researcher in interpreter design and runtime optimization, he explores the trade offs between AST based and bytecode based execution models, and their impacts on performance and tooling.
![Screenshot 2025-07-04 at 15.34.33](https://hackmd.io/_uploads/SJoNK8SSll.png)

3. **[Stefan Marr](https://www.kent.ac.uk/school-of-computing/people/3167/marr-stefan)**
   A Senior Lecturer and Royal Society Industry Fellow, he researches programming language implementation techniques, focusing on combining concurrency models safely and building tools to detect and prevent subtle concurrency issues in complex systems.
   ![Screenshot 2025-07-04 at 15.35.11](https://hackmd.io/_uploads/HkzsdIrreg.png)


You can find all the mails sent in the same directory with `[name]_Emails.pdf`

Unfortunatly we didn't get any response from Michael Vollmer.

#### Mobilizing the Right Resources in Case of Technical Issues

While working on JS-CMP, our C++ based JavaScript transpiler, we encountered a key technical limitation: C++ lacks direct equivalents for several JavaScript operators, such as the unsigned right shift (`>>>`), `delete`, `void`, and `typeof`. These operators are fundamental to JavaScript’s semantics, and omitting them would compromise compatibility.

To address this, we first discussed possible approaches with our mentor (expert in compiler). We proposed simulating some of these operators using advanced macro techniques in C++. As a starting point, we examined how low level C/C++ macros are used in large scale projects like the Linux kernel—particularly the `container_of` macro described in [this blog post](https://radek.io/posts/magical-container_of-macro/) and implemented in [list.h](https://github.com/torvalds/linux/blob/master/include/linux/list.h).

Through this research, we discovered [IdOp](https://github.com/cogwheel/IdOp), a C++ header only library that enables limited forms of custom operator overloading using identifiers. While promising, IdOp wasn’t flexible enough for our needs—it lacked the adaptability and extensibility we required to support JavaScript’s dynamic behavior.

As a result, we shifted focus to make a custom robust solution: [SyntaxSmith](https://github.com/SimonBandiera/SyntaxSmith). This project offered a more general approach to parsing and rewriting C++ expressions, making it a better fit for our goal of emulating JavaScript operators in a maintainable and scalable way. With it, we aim to integrate operator support into our transpilation process more seamlessly, all while keeping the C++ output readable and consistent with JavaScript logic.
