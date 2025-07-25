export module item;

import <string>;
import <memory>;
import <vector>;
import position;

export class Item {
protected:
    int x;
    int y;
    Position p;

public:
    Item(int x, int y);
    virtual ~Item();

    int getX() const;
    int getY() const;
    Position getPosition();

    // Reset the position
    void setPosition(int x, int y);

    virtual int getValue() = 0;

    // getType will return the preset number ('0' - '9') of each item
    virtual char getType() = 0;

    // use will return a string to represent the potion 
    //  or an int of it's applied on treasure
    // NEED TO BE FIXED //
    // Either overload use or make it return the same type
    virtual std::string use() = 0;

    // Symbol representation of potion "P" or treasure "G"
    virtual char getSymbol() const = 0;

    virtual bool isPotion() const = 0;

    virtual bool canCollect() = 0;

    virtual void changeStatus () = 0;

    virtual void changeCollectStatus () = 0;

    virtual void See() = 0;

    virtual bool isSeen() = 0;

    // Check if an item is a dragon hoard, defaulted to false
    virtual bool isDragonHoard() = 0;
};
