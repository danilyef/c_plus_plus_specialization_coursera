#### Programming Task: "Text Editor"

Let's consider a simplified text editor supporting the following set of commands:

1. Moving the cursor left (Left) and right (Right) by one position.
2. Inputting a character at the current cursor position (Insert).
3. Copying a fragment of text starting from the current cursor position to the clipboard (Copy).
4. Cutting a fragment of text similar to copying, followed by deleting the copied characters from the text (Cut).
5. Pasting the contents of the clipboard into the current cursor position (Paste).

These commands are indeed supported by almost any text editor. Also, there are standard rules defining their effects:

- If the editor contains a text of length n characters, then the cursor can be in one of (n + 1) possible positions. For example, let's denote the cursor with a vertical bar | (we'll use this notation later), then in the text abc, the cursor can be positioned in 4 positions: |abc, a|bc, ab|c, abc|. Therefore, the Left command has no effect when the cursor is at the beginning of the text, and Right has no effect when the cursor is at the end. In particular, neither Left nor Right have any effect when the editor does not contain text.

- The entered character is placed at the cursor position, shifting the cursor and all text to its right by one position to the right. Similarly, when inserting a fragment of length n, the cursor and the text to its right are shifted n positions to the right. The table below provides examples demonstrating this rule.


The clipboard is initially empty. Inserting an empty fragment has no effect. The content of the clipboard is not cleared after pasting and remains unchanged until the next Copy or Cut command. Copying or cutting a fragment of zero length has no effect on the text but empties the clipboard. The cursor does not move either when copying or cutting text. For example, after cutting a three-character fragment from the text ab|cdef, we get the text ab|f.

You are tasked with implementing the "core" of a text editor, supporting all the described operations, in the form of an Editor class, with the following interface:

```cpp
class Editor {
public:
  Editor();
  void Left();   // move cursor left
  void Right();  // move cursor right
  void Insert(char token);   // insert character token
  void Copy(size_t tokens);  // copy up to tokens characters,
                             // starting from the current cursor position
  void Cut(size_t tokens);  // cut up to tokens characters,
                            // starting from the current cursor position
  void Paste();  // paste the contents of the clipboard
                 // into the current cursor position
  string GetText() const;  // get the current content
                           // of the text editor as a string
};
```

As you can notice, each described command corresponds to a method of the Editor class. Also, there is a method GetText(), allowing to obtain the current content of the editor as a string. Comments for the methods Cut(size_t tokens) and Copy(size_t tokens) indicate that a fragment of length not exceeding tokens characters goes into the clipboard — this means that if there are fewer than tokens characters to the right of the cursor, the methods Cut() and Copy() should cut/copy all characters to the right.

**Constraints:**
- The implementation of the Editor class should handle up to 10^6 requests in no more than 1 second. It is guaranteed that:
  - The length of the text never exceeds 10^6 characters.
  - The methods Copy() and Cut() together copy/cut no more than 10^6 characters.
  - The method GetText() is called once in each test.

**Example:**

```cpp
int main() {
  Editor editor;
  const string text = "hello, world";
  for (char c : text) {
    editor.Insert(c);
  }
  // Current state of the editor: `hello, world|`
  for (size_t i = 0; i < text.size(); ++i) {
    editor.Left();
  }
  // Current state of the editor: `|hello, world`
  editor.Cut(7);
  // Current state of the editor: `|world`
  // The text `hello, ` is in the clipboard
  for (size_t i = 0; i < 5; ++i) {
    editor.Right();
  }
  // Current state of the editor: `world|`
  editor.Insert(',');
  editor.Insert(' ');
  // Current state of the editor: `world, |`
  editor.Paste();
  // Current state of the editor: `world, hello, |`
  editor.Left();
  editor.Left();
  // Current state of the editor: `world, hello|, `
  editor.Cut(3); // 2 characters will be cut
  // Current state of the editor: `world, hello|`
  cout << editor.GetText();
}
```

**Output:**

```
world, hello
```
