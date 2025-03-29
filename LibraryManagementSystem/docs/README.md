# Library Management System

## Overview
The Library Management System is designed to manage books, members, and library operations efficiently. It involves three main classes:

- **Book**: Represents a book in the library.
- **Member**: Represents a library member.
- **Library**: Manages books and members.

This system includes multiple constructors, constraints, and utility methods to ensure smooth library operations.

## Features

### Book Class
- **Attributes:**
  - `title` (public): Book title.
  - `author` (public): Author name.
  - `isbn` (private): Unique book identifier.
  - `copiesAvailable` (private): Available copies.
  - `totalCopies` (private): Total copies in the library.

- **Methods:**
  - Constructors: Parameterized, default, and copy constructor.
  - Getters and setters.
  - `borrowBook()`: Decreases `copiesAvailable` if available.
  - `returnBook()`: Increases `copiesAvailable` up to `totalCopies`.
  - `printDetails()`: Prints book details.

- **Constraints:**
  - Unique ISBN for each book.
  - `copiesAvailable` should never exceed `totalCopies` or be negative.

### Member Class
- **Attributes:**
  - `memberID` (private): Unique identifier.
  - `name` (public): Member name.
  - `borrowedBooks` (private): Map of borrowed books (ISBN to quantity).
  - `borrowLimit` (private): Max books a member can borrow (default: 3).

- **Methods:**
  - Constructors: Parameterized and default.
  - `borrowBook(isbn)`: Allows borrowing within the limit.
  - `returnBook(isbn)`: Allows returning borrowed books.
  - `printDetails()`: Prints member details and borrowed books.

- **Constraints:**
  - Cannot exceed `borrowLimit`.
  - Can borrow the same book multiple times if available.

### Library Class
- **Attributes:**
  - `books` (private): List of books.
  - `members` (private): List of registered members.

- **Methods:**
  - `addBook(Book&)`: Adds a book if ISBN is unique.
  - `registerMember(Member&)`: Registers a member if `memberID` is unique.
  - `borrowBook(memberID, isbn)`: Manages borrowing logic.
  - `returnBook(memberID, isbn)`: Handles book returns.
  - `printLibraryDetails()`: Prints details of books and members.

- **Constraints:**
  - No duplicate books (based on ISBN) or members.

## Constraints
- Max 50 books in the library.
- Max 150 members.
- Each book can have up to 15 copies.
- Each member can borrow up to 15 books at a time.

## Edge Cases Handled
- Borrowing a book with no available copies.
- Returning a book not borrowed by the member.
- Handling invalid ISBNs or member IDs.

## Input Format
- `Book Title Author ISBN CopiesAvailable TotalCopies`
- `UpdateCopiesCount ISBN NewCount`
- `Member MemberID Name BorrowLimit`
- `Borrow MemberID ISBN`
- `Return MemberID ISBN`
- `PrintBook ISBN`
- `PrintMember MemberID`
- `PrintLibrary`
- `Done` (End of input)

## Output Format
- `PrintBook`: `Title Author`
- `PrintMember`: `MemberID Name ISBN NumberOfBorrowedCopies`
- `PrintLibrary`: List of books and members.

## Error Messages
- Constraints violations print relevant error messages (e.g., "Invalid request! Borrow limit exceeded").

