### Version Control Software in C (git)

# Compilation 

Compilation: *make*
Delete .o files and those create(refs,branch...): *make clean*

# Command 

*./myGit list-refs*: displays all existing references.

*./myGit create-ref <name> <hash>*: creates the reference <name> that points to the commit corresponding to the given hash.

*./myGit delete-ref <name>*: deletes the reference name.

*./myGit add <elem> [<elem2> <elem3> ...]*: adds one or more files/directories to the staging area (to be part of the next commit).

*./myGit list-add*: displays the contents of the staging area.

*./myGit clear-add*: clears the staging area.

*./myGit commit <branch name> [-m <message>]*: performs a commit on a branch, with or without a descriptive message.

*./myGit get-current-branch*: displays the name of the current branch.

*./myGit branch <branch-name>*: creates a branch named <branch-name> if it doesn't already exist. If the branch already exists, the command should display an error message.

*./myGit branch-print <branch-name>:* displays the hash of all commits in the branch, accompanied by their optional descriptive message. If the branch doesn't exist, an error message is displayed.

*./myGit checkout-branch <branch-name>*: moves to the <branch-name> branch. If this branch doesn't exist, an error message is displayed.

*./myGit checkout-commit <pattern>*: moves to the commit that starts with <pattern>. Error messages are displayed when <pattern> doesn't match exactly one commit."

*./myGit merge <branch> <message>*, and depending on the cases, the following processing should be applied:

    If there are no conflicts between the current branch and the <branch> branch, the merge is performed (using the merge function), and a message is displayed to the user indicating that the fusion has been successful.

    If there are conflicts, the user should be prompted to choose one of the following options:
        Keep the files from the current branch and create a deletion commit for the <branch> branch before invoking the merge function.

        Keep the files from the <branch> branch and create a deletion commit for the current branch before invoking the merge function.

        Manually choose, conflict by conflict, the branch on which the conflicting file/directory should be kept. In this case, the list of conflicts needs to be divided into two lists based on the user's input. Then, a deletion commit should be created for each branch with these two lists before performing the merge using the merge function.