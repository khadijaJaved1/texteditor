#include <iostream>
#include <vector>
#include <stack>
#include <string>

using namespace std;

class TextEditor {
    vector<char> text;
    int cursorPosition;
    stack<string> undoStack;
    stack<string> redoStack;

    void saveState(stack<string>& stack) {
        stack.push(string(text.begin(), text.end()));
    }

public:
    TextEditor() : cursorPosition(0) {}

    void insert(char ch) {
        saveState(undoStack);
        text.insert(text.begin() + cursorPosition, ch);
        cursorPosition++;
        while (!redoStack.empty()) redoStack.pop();
    }

    void del() {
        if (cursorPosition > 0) {
            saveState(undoStack);
            text.erase(text.begin() + cursorPosition - 1);
            cursorPosition--;
            while (!redoStack.empty()) redoStack.pop();
        }
    }

    void undo() {
        if (!undoStack.empty()) {
            saveState(redoStack);
            text.assign(undoStack.top().begin(), undoStack.top().end());
            undoStack.pop();
            cursorPosition = text.size();
        }
    }

    void redo() {
        if (!redoStack.empty()) {
            saveState(undoStack);
            text.assign(redoStack.top().begin(), redoStack.top().end());
            redoStack.pop();
            cursorPosition = text.size();
        }
    }

    void next() {
        if (cursorPosition < text.size()) cursorPosition++;
    }

    void previous() {
        if (cursorPosition > 0) cursorPosition--;
    }

    void start() {
        cursorPosition = 0;
    }

    void end() {
        cursorPosition = text.size();
    }

    void curr_position(int pos) {
        if (pos >= 0 && pos <= text.size()) cursorPosition = pos;
    }

    void display() {
        for (char ch : text) cout << ch;
        cout << endl;
    }
};

int main() {
    TextEditor editor;
    editor.insert('K');
    editor.insert('H');
    editor.insert('A');
    editor.insert('D');
    editor.insert('I');
    editor.insert('J');
    editor.insert('A');
    editor.display();

    editor.undo();
    editor.display();

    editor.redo();
    editor.display();

    return 0;
}
