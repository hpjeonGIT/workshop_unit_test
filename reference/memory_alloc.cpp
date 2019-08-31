#include<vector>
#include<iostream>
#include<memory>

int main(int argc, char** argv) {
    
    uint npt;
    std::cin >> npt;    
    std::cout << " npt = " << npt << std::endl;

    // resize in STL
    std::vector<double> arr1;
    arr1.resize(npt);
    std::cout << arr1.size() << std::endl;
    // allocation from STL
    std::vector<double> arr2(npt);
    std::cout << arr2.size() << std::endl;
    std::cout << arr2[0] << std::endl;
    // Variable length array (VLA)
    double xm[npt];
    std::cout << sizeof(xm) << std::endl;
    std::cout << xm[0] << " " << xm[npt-1] << std::endl;
    // smart pointer
    std::unique_ptr<double []> ff(new double [npt]);
    std::cout << sizeof(ff)*npt <<  " " << ff[0] << " " << ff[npt-1] << std::endl;
    // new/delete - avoid this when possible
    double *xv;
    xv = new double [npt];
    std::cout << sizeof(xv) << " " << xv[0] << " " << xv[npt-1] << std::endl;
    delete [] xv;
    
    return 0;
}
