# samsh - A basic C shell
---
SAMSH is a simple implementation of a shell in C.t demonstrates the basics of how a shell works.That is: read, parse, fork, exec, and wait.  Since its purpose is learning (not feature completeness or even fitness for casual use), it has many limitations, including:
* Commands must be on a single line.
* Arguments must be separated by whitespace.
* No quoting arguments or escaping whitespace.
* No piping or redirection.
* Only builtins are: `cd`, `help`, `exit`.

## Contributing
------------
New contributions are always welcome from fellow developers who are interested in learning the dynamics of a shell. Just follow the given guidelines :
* Create your own forn of the repo
* Migrate to a new branch
* Implement your changes
* Open a pull request for the changes and provide a detailed enough description of your work.

## Todos
---
There is a lot of scope of improvement in the shell. Pick one from the list below:
1. Implementing Tab completion
2. You can implement one of the following builtins :
  * `alias`
  * `logout`
  * `enable`
  * `declare`
3. Implementing config files.
4. Implementing history-record and up arrow command display.

## License
-------

This code is in the public domain (see [UNLICENSE](UNLICENSE) for more details). This means you can use, modify, and distribute it without any restriction. I appreciate, but don't require, acknowledgement in derivative works.
