#include <cstring>
#include <iostream>

#include "../include/sorting_networks.h"

using namespace sorting_networks;

template <class OS> void output_graph(OS &ostr, unsigned int n) {
  using C = typename io_details::OutputContainerPassthrough<OS>;
  C dummy_container(ostr, n);
  sorting_network<C, io_details::OutputGraphSwap<OS>>(dummy_container, n, 0, 1);
}

template <class OS> void output_pseudocode(OS &ostr, unsigned int n) {
  using C = typename io_details::OutputContainerPassthrough<OS>;
  C dummy_container(ostr, n);
  sorting_network<C, io_details::OutputSwap<OS>>(dummy_container, n, 0, 1);
}

// Add Fortran sorting subroutine output
template <class OS> void output_fortran(OS &ostr, unsigned int n) {
  using C = typename io_details::OutputContainerPassthrough<OS>;
  C dummy_container(ostr, n);

  sorting_network<C, io_details::OutputSwapFortran<OS>>(dummy_container, n, 0, 1);
}


void print_usage() {

  std::cout << "Usage\n";
  std::cout << '\n';
  std::cout << "  sngenerator [-graph] <number of elements>\n";
  std::cout << '\n';
  std::cout << "Output pseudocode, or optionally a graph for a Batcher "
               "odd/even sorting network.\n";
  std::cout << '\n';
}

// Print a subroutine
void print_subroutine(unsigned int n_items) {

   std::cout << "    pure subroutine sort_IKIND_"<<n_items<<"(x) \n";
   std::cout << "        integer(IKIND), intent(inout) :: x("<<n_items<<") \n";


   output_fortran(std::cout, n_items);

   std::cout << "    end subroutine sort_IKIND_"<<n_items<<" \n";

}


int main(int argc, char *argv[]) {

  int n = std::atoi(argv[argc - 1]);
  if (n < 1) {
    std::cerr << "Argument must be an integer greater than zero.\n";
    return 1;
  }

  unsigned int max_n = 64;

  std::cout<<"module fast_sorting\n";
  std::cout<<"    use iso_fortran_env\n";
  std::cout<<"    implicit none\n";
  std::cout<<"    private\n";
  std::cout<<"\n";
  std::cout<<"    integer, parameter :: IKIND = int32\n";
  std::cout<<"\n";
  std::cout<<"    public :: sort_IKIND \n";
  std::cout<<"\n";
  std::cout<<"    contains\n";
  std::cout<<"    pure subroutine sort_IKIND(x)\n";
  std::cout<<"        integer(IKIND), intent(inout) :: x(:)\n";
  std::cout<<"        select case (size(x))\n";
  std::cout<<"            case (1); return\n";
  for (unsigned int n_items = 2; n_items<=max_n; n_items++) {
    std::cout<<"            case ("<<n_items<<"); call sort_IKIND_"<<n_items<<"(x) \n";
  }
  std::cout<<"            case default; return ! not handling the large array case yet \n";
  std::cout<<"        end select \n";
  std::cout<<"    end subroutine sort_IKIND\n\n\n";
  std::cout<<"    ! Compare and sort\n";
  std::cout<<"    elemental subroutine a_lt_b(a,b)\n";
  std::cout<<"      integer(IKIND), intent(inout) :: a,b\n";
  std::cout<<"      integer(IKIND) :: tmp\n";
  std::cout<<"      if (a>b) then\n";
  std::cout<<"         tmp = a\n";
  std::cout<<"         a   = b\n";
  std::cout<<"         b   = tmp\n";
  std::cout<<"      end if\n";
  std::cout<<"    end subroutine a_lt_b \n\n";



  for (unsigned int n_items = 2; n_items<=max_n; n_items++) {

    print_subroutine(n_items);

  }

  std::cout<<"end module fast_sorting_IKIND\n";


  unsigned int n_items = n;
//  if (print_graph)
//    output_graph(std::cout, n);
//  else
    //print_subroutine(n_items);
  return 0;
}
