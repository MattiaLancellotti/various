// Just some tests in golang
package collection

/* struct Stack { char *data; };
 * typedef Stack_t Stack;
 */
type Stack struct {
     data []string
}

func (s *Stack) Push(x string) {
     s.data = append(s.data, x)
}

func (s *Stack) Pop() string {
     n := len(s.data) - 1
     res := s.data[n]

     s.data[n] = ""
     s.data = s.data[:n]
     return res
}

func (s *Stack) Size() int {
     return len(s.data)
}
