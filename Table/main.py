import math


def num_arr_to_str_arr(num_arr):
    str_arr = []
    for i in range(len(num_arr)):
        str_arr.append(str(num_arr[i]))
    return str_arr


def strs_arr_length(strs):
    len_arr = []
    for i in range(len(strs)):
        len_arr.append(len(strs[i]))
    return len_arr


def str_to_right_corn(string_, length):
    return ' ' * (length - len(string_)) + string_


def str_to_left_corn(string_, length):
    return string_ + ' ' * (length - len(string_))


def str_to_center(string_, length):
    return ' ' * math.ceil((length - len(string_)) / 2) + string_ + ' ' * math.floor((length - len(string_)) / 2)


def strs_alignment(align_func, index, strs):
    return align_func(strs[index], max(strs_arr_length(strs)))


def column_with_alignment(strs, align_type='left'):
    column = ''
    if align_type == 'right':
        align_func = str_to_right_corn
    elif align_type == 'center':
        align_func = str_to_center
    else:
        align_func = str_to_left_corn
    for i in range(len(strs)):
        column = column + strs_alignment(align_func, i, strs) + '\n'
    return column[:-1]


class Table:
    def __init__(self,
                 rows=0,
                 columns=0,
                 def_cell_length=1,
                 def_cell_height=1,
                 def_cell_type="string",
                 def_cell_align="left",
                 def_cell_format="",
                 def_col_sep="│",
                 def_row_sep="─",
                 def_top_left_sep="┌",
                 def_top_right_sep="┐",
                 def_bottom_left_sep="└",
                 def_bottom_right_sep="┘"):
        self.rows = rows
        self.columns = columns
        self.def_cell_length = def_cell_length
        self.def_cell_height = def_cell_height
        self.def_cell_type = def_cell_type
        self.def_cell_align = def_cell_align
        self.def_cell_format = def_cell_format
        self.def_col_sep = def_col_sep
        self.def_row_sep = def_row_sep
        self.def_top_left_sep = def_top_left_sep
        self.def_top_right_sep = def_top_right_sep
        self.def_bottom_left_sep = def_bottom_left_sep
        self.def_bottom_right_sep = def_bottom_right_sep
        self.arr = self.create_arr()

    def create_arr(self):
        return [[self.new_cell() for i in range(self.columns)] for j in range(self.rows)]

    def new_cell(self,
                 content="",
                 length=None,
                 height=None,
                 align=None,
                 cell_type=None,
                 cell_format=None,
                 row_sep=None,
                 col_sep=None,
                 top_left_sep=None,
                 top_right_sep=None,
                 bottom_left_sep=None,
                 bottom_right_sep=None):
        return {"content": content,
                "length": length if length is not None else self.def_cell_length,
                "height": height if height is not None else self.def_cell_height,
                "align": align if align is not None else self.def_cell_align,
                "type": cell_type if cell_type is not None else self.def_cell_type,
                "format": cell_format if cell_format is not None else self.def_cell_format,
                "top_sep": row_sep if row_sep is not None else self.def_row_sep,
                "bottom_sep": row_sep if row_sep is not None else self.def_row_sep,
                "left_sep": col_sep if col_sep is not None else self.def_col_sep,
                "right_sep": col_sep if col_sep is not None else self.def_col_sep}

    def new_row(self):
        pass
    
    def edit_cell(self,
                  row_num,
                  col_num,
                  content=None,
                  length=None,
                  height=None,
                  align=None,
                  cell_type=None,
                  cell_format=None#,
                  #row_sep=None,
                  #col_sep=None
                  ):
        if content != self.arr[row_num - 1][col_num - 1]["content"] and content is not None:
            self.arr[row_num - 1][col_num - 1]["content"] = content
        if length != self.arr[row_num - 1][col_num - 1]["length"] and length is not None:
            self.arr[row_num - 1][col_num - 1]["length"] = length
        if height != self.arr[row_num - 1][col_num - 1]["height"] and height is not None:
            self.arr[row_num - 1][col_num - 1]["height"] = height
        if align != self.arr[row_num - 1][col_num - 1]["align"] and align is not None:
            self.arr[row_num - 1][col_num - 1]["align"] = align
        if cell_type != self.arr[row_num - 1][col_num - 1]["type"] and cell_type is not None:
            self.arr[row_num - 1][col_num - 1]["type"] = cell_type
        if cell_format != self.arr[row_num - 1][col_num - 1]["format"] and cell_format is not None:
            self.arr[row_num - 1][col_num - 1]["format"] = cell_format #todo
#         if row_sep != self.arr[row_num - 1][col_num - 1]["row_sep"] and row_sep is not None:
#             self.arr[row_num - 1][col_num - 1]["row_sep"] = row_sep
#         if col_sep != self.arr[row_num - 1][col_num - 1]["col_sep"] and col_sep is not None:
#             self.arr[row_num - 1][col_num - 1]["col_sep"] = col_sep

    def edit_arr(self,
                 content_arr=((None,),),
                 length_arr=((None,),),
                 height_arr=((None,),),
                 align_arr=((None,),),
                 cell_type_arr=((None,),),
                 cell_format_arr=((None,),)#,
                 #row_sep_arr=None,
                 #col_sep_arr=None
                 ):
        for row in range(max([len(content_arr), len(length_arr), len(align_arr), len(cell_type_arr), len(cell_format_arr)])):
            for column in range(max([len(content_arr[0]), len(length_arr[0]), len(align_arr[0]), len(cell_type_arr[0]), len(cell_format_arr[0])])):
                self.edit_cell(row + 1, column + 1,
                               content=None if content_arr == ((None,),) else content_arr[row][column],
                               length=None if length_arr == ((None,),) else length_arr[row][column],
                               height=None if height_arr == ((None,),) else height_arr[row][column],
                               align=None if align_arr == ((None,),) else align_arr[row][column],
                               cell_type=None if cell_type_arr == ((None,),) else cell_type_arr[row][column],
                               cell_format=None if cell_format_arr == ((None,),) else cell_format_arr[row][column])

    def str_to_right_corn(self, string_, length, filling=" "):
        return filling[0] * (length - len(string_)) + string_


    def str_to_left_corn(self, string_, length, filling=" "):
        return string_ + filling[0] * (length - len(string_))


    def str_to_center(self, string_, length, filling=" "):
        return filling[0] * math.ceil((length - len(string_)) / 2) + string_ + filling[0] * math.floor((length - len(string_)) / 2)

    def cell_to_string(self, row, col):
        cell = self.arr[row][col]
        if cell["align"] == "right":
            string_ = self.str_to_right_corn(cell["content"], cell["length"])
        elif cell["align"] == "center":
            string_ = self.str_to_center(cell["content"], cell["length"])
        else:
            string_ = self.str_to_left_corn(cell["content"], cell["length"])
        return string_[:cell["length"]]

    def __str__(self):
        res_str = ""
        for row in range(self.rows):
            for col in range(self.columns):
                res_str += self.cell_to_string(row, col)
            res_str += "\n"
        return res_str[:-1]
    
#     def __repr__(self):
#         return self.__str__()
    
    def __getitem__(self, i):
        return self.arr[i]


table1 = Table(rows=2, columns=3)
table1.edit_arr(content_arr=[["11", "12", "13"], ["21", "22", "23"]], length_arr=[[10, 10, 10], [10, 10, 10]])
print(table1[0][0])
#print(f"size is [{table1.columns}, {table1.rows}]")
