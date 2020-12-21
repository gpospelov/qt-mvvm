# Revision of SessionItem API

## Setting data

> When acting through the item, command service invoked.

SessionItem::setData
- model ? model->command->execute : setDataIntern

SessionItem::setDataIntern
- m_data->setData
- model -> mapper()

SetValueCommand::execute()
- item->setDataIntern()

## Insert Item

> When acting through item, no command service.

SessionItem::insertItem(item, tagrow)
- m_tags->inserItem
- item->setParent(this), item->setModel
- model->mapper() 

InsertNewItemCommand
-item->inserItem()

## TakeItem

SessionItem::takeItem
- model->mapper->aboutToRemove
- item->setParent(nullptr), item->setModel(nullptr)
- tags->takeItem
- model->mapper->itemRemoved


<hr>

## Investigating API

```
    Total matches (qt-mvvm, darefl)

    // 51 matches (11 mvvm, 7 darefl)
    // OK
    model_type modelType() const;

    // 32 matches (9 mvvm, 1 darefl)
    // OK
    virtual std::string displayName() const;

    // 85 matches (73 mvvm, 43 darefl)
    // OK
    virtual SessionItem* setDisplayName(const std::string& name);

    // 73 matches (7 mvvm, 5 darefl)
    // OK
    std::string identifier() const;

    // 65 matches (22 mvvm, 1 darefl)
    // ?
    template <typename T> bool setData(const T& value, int role = ItemDataRole::DATA);

    // 6 matches (6 mvvm, 0 darefl)
    // ?
    bool setDataIntern(const Variant& variant, int role);

    // 27 matches (11 mvvm, 0 darefl)
    // ?
    bool hasData(int role = ItemDataRole::DATA) const;

    // 89 matches (25 mvvm, 1 darefl)
    // OK
    template <typename T> T data(int role = ItemDataRole::DATA) const;

    // 47 matches (41 mvvm, 6 darefl)
    // OK
    SessionModel* model() const;

    // 41 matches (29 mvvm, 9 darefl)
    // OK
    SessionItem* parent() const;

    // 77 matches (4 mvvm, 2 darefl)
    // ?
    int childrenCount() const;

    // 75 matches ( 12 mvvm, 0 darefl)
    // OK
    bool insertItem(SessionItem* item, const TagRow& tagrow);

    // 18 matches (8 mvvm, 0 darefl)
    // OK
    SessionItem* takeItem(const TagRow& tagrow);

    // 68 matches (18 mvvm, 6 darefl)
    // OK
    std::vector<SessionItem*> children() const;

    // 16 matches (2 mvvm, 0 darefl) 
    // REMOVE
    std::vector<int> roles() const;

    // 6 matches (2 mvvm, 0 darefl)
    // REMOVE
    std::string defaultTag() const;

    // 2 matches (2 mvvm, 0 darefl)
    // REMOVE
    void setDefaultTag(const std::string& tag);

    // 53 matches (16 mvvm, 2 darefl) 
    // REFACTOR
    void registerTag(const TagInfo& tagInfo, bool set_as_default = false);

    // 12 matches (2 mvvm, 1 darefl)
    // REMOVE
    bool isTag(const std::string& name) const;

    // 12 matches (3 mvvm, 1 darefl)
    // REMOVE
    std::string tag() const;

    // 19 matches (9 mvvm, 6 darefl) 
    // OK
    TagRow tagRow() const;

    // 12 matches (10 mvvm, 1 darefl)
    // REFACTOR
    int itemCount(const std::string& tag) const;

    // 57 matches (19 mvvm, 9 mvvm)
    // REFACTOR
    SessionItem* getItem(const std::string& tag, int row = 0) const; // FIXME TagRow?
    
    // 16 matches (3 mvvm, 1 mvvm)
    // REFACTOR
    std::vector<SessionItem*> getItems(const std::string& tag) const;

    // 28 matches (22 mvvm, 15 darefl)
    // OK
    template <typename T> T* item(const std::string& tag) const;

    // 10 matches (7 mvvm, 3 darefl) 
    // OK
    template <typename T = SessionItem> std::vector<T*> items(const std::string& tag) const;

    // 12 matches (6 mvvm, 0 darefl)
    // REMOVE
    std::string tagOfItem(const SessionItem* item) const;

    // 16 matches (6 mvvm, 0 darefl)
    // OK
    TagRow tagRowOfItem(const SessionItem* item) const;

    // 27 matches (16 mvvm, 4 darefl) 
    // OK
    ItemMapper* mapper();

    // 7 matches ( 4 mvvm, 0 darefl)
    // ?
    bool isEditable() const;

    // 8 matches (7 mvvm, 0 darefl)
    // OK
    SessionItem* setEditable(bool value, 0 darefl);

    // 10 matches (7 mvvm, 0 darefl)
    // ?
    bool isEnabled() const;

    // 7 matches (4 mvvm, 0 darefl)
    // OK
    SessionItem* setEnabled(bool value);

    // 12 matches (3 mvvm, 0 darefl)
    // ?
    std::string toolTip() const;

    // 18 matches (6 mvvm, 1 darefl)
    // OK
    SessionItem* setToolTip(const std::string& tooltip);

    // 5 matches (3 mvv, 0 dareflm)
    // ?
    std::string editorType() const;

    // 5 matches (3 mvvm, 0 darefl)
    // OK
    SessionItem* setEditorType(const std::string& editor_type);

    // 15 matches (6 mvvm, 0 darefl)
    // DONE: REMOVE
    bool isSinglePropertyTag(const std::string& tag) const;

    // 86 matches (47 mvvm, 84 darefl)
    // OK
    template <typename T> T property(const std::string& tag) const;

    // 43 matches (41 mvvm, 17 darefl)
    // OK
    template <typename T> void setProperty(const std::string& tag, const T& value);
    void setProperty(const std::string& tag, const char* value);

    // 10 matches (7 mvvm, 0 darefl)
    // OK
    SessionItemData* itemData();
    const SessionItemData* itemData() const;

```
