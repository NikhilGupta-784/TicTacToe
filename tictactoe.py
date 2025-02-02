"""
Tic Tac Toe Player
"""

import math
import copy 

X = "X"
O = "O"
EMPTY = None


def initial_state():
    """
    Returns starting state of the board.
    """
    return [[EMPTY, EMPTY, EMPTY],
            [EMPTY, EMPTY, EMPTY],
            [EMPTY, EMPTY, EMPTY]]


def player(board):
    """
    Returns player who has the next turn on a board.
    """
    count = 0
    for i in board:
        for j in i:
            if j is None:
                count +=1

    
    if board == initial_state():
        return X
    elif count % 2 == 0:
        return O
    elif count % 2 == 1:
        return X
    else:
        return X
    
    #raise NotImplementedError


def actions(board):
    """
    Returns set of all possible actions (i, j) available on the board.
    """
    cell = set()
    for i in range(3):
        for j in range(3):
            if board[i][j] is None:
                cell.add((i,j))
    return cell

    #raise NotImplementedError


def result(board, action):
    """
    Returns the board that results from making move (i, j) on the board.
    """

    #creating a deepcopy of the board
    board_copy = copy.deepcopy(board)
    if board[action[0]][action[1]] is None:
        board_copy[action[0]][action[1]]=player(board)
        return board_copy
    else:
        raise Exception("InvalidMove")

    
    #raise NotImplementedError


def winner(board):
    """
    Returns the winner of the game, if there is one.
    """

    #row check
    for row in board:
        if row.count(X) == 3:
            return X
        elif row.count(O) == 3:
            return O
    
    #column check 
    for j in range(3):
        if board[0][j] == board[1][j] == board[2][j] != EMPTY:
            return board[0][j]

    #diagnol check 
    if board[0][0] == board[1][1] == board[2][2] != EMPTY:
        return board[0][0]
    if board[0][2] == board[1][1] == board[2][0] != EMPTY:
        return board[0][2]
    
    
    return None


    #raise NotImplementedError


def terminal(board):
    """
    Returns True if game is over, False otherwise.
    """

    #counting number of Empty cells
    count_none = 0
    for i in board:
        for j in i:
            if j is None:
                count_none +=1
    
    if winner(board) is not None:   #condition if any player has won 
        return True 
    elif winner(board) is None and count_none == 0:  #condition for either a tie or all the cells have been filled 
        return True
    else:          # game still in process 
        return False
        

    #raise NotImplementedError


def utility(board):
    """
    Returns 1 if X has won the game, -1 if O has won, 0 otherwise.
    """
    if winner(board) == X:
        return 1
    elif winner(board) == O:
        return -1
    else:
        return 0
    
    #raise NotImplementedError


def minimax(board):
    """
    Returns the optimal action for the current player on the board.
    """

    #returns max value of the boards (X)
    def max_value(board):
        if terminal(board):
            return utility(board)
        v = float('-inf')
        for i in actions(board):
            v = max(v,min_value(result(board,i)))
        return v
    
    #returns min value of the board (O)
    def min_value(board):
        if terminal(board):
            return utility(board)
        v = float('+inf')
        for i in actions(board):
            v = min(v,max_value(result(board,i)))
        return v
    
    #depending upon the player it returns the best optimal action for the computer to play 
    if player(board) == X:
        return max(actions(board), key = lambda action : min_value(result(board,action)))
    else:
        return min(actions(board), key = lambda action : max_value(result(board,action)))
        

    #raise NotImplementedError
