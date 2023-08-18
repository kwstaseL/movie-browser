#ifndef FILTERABLEWIDGET_H
#define FILTERABLEWIDGET_H

#include "Widget.h"

// Using virtual to handle the diamond problem 
class FilterableWidget : public virtual Widget
{
protected:

    virtual bool hasRequirements(const Movie* const movie) const;

protected:

    std::vector<WidgetEnums::WidgetFilters> filterToBeChecked{};

public:

    FilterableWidget();
    FilterableWidget(bool invisible);
};




#endif