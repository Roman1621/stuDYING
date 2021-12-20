#ifndef FIELD_VIEW_H
#define FIELD_VIEW_H

#include "..//headers/field.h"

class Field_view{
    private:
        Field& view;

    public:
        Field_view(Field& view_f);
        void display();
};

#endif
