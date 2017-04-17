#include "TFile.h"
#include "Sclass.h"
#include "TObjArray.h"
#include "TObject.h"

void write_it() {
    std::cout << "write it ... " << std::endl;
    // create a new file
    TFile* f = TFile::Open("test.root", "recreate");

    // create the objects
    Sclass* obj = new Sclass();
    obj->SetX(42.1);
    obj->SetY(1.24);

    TObjArray *TObj=new TObjArray();
    TObj->Add(obj);
    TObj->Write("anObjectArray",TObject::kSingleKey);
    printf("%d\n",TObj->GetEntries());

    // close it
    f->Close();
    std::cout << "write it done. " << std::endl;
}

void read_it() {
    std::cout << "read it ... " << std::endl;
    // open the file
    TFile* f = TFile::Open("test.root");
    if (!f) {
        std::cerr << "Can't open file test.root." << std::endl;
        return;
    }

    TObjArray* TObj1 = dynamic_cast<TObjArray*>(f->Get("anObjectArray"));

     if (!TObj1) {
        std::cerr << "Can't find the anObjectArray" << std::endl;
        return;
    }

    Sclass* sclass = dynamic_cast<Sclass*>((*TObj1)[1]);
    if(sclass == NULL)
    {
  	std::cout << "the object is error. " << std::endl;
        break;
    }

    sclass->Print();

    /*for(int i=0;i<TObj1->GetEntries();i++)
    {
	printf("%f\n",TObj1[i]);
    }*/


    std::cout << "read it done. " << std::endl;

}

void read_write() {
    write_it();
    read_it();
}

int main() {
    read_write();
}
