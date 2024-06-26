#include "viewboard.h"

ViewBoard::ViewBoard(QObject *parent)
    : QAbstractItemModel(parent)
{
}

QVariant ViewBoard::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
}

QModelIndex ViewBoard::index(int row, int column, const QModelIndex &parent) const
{
    // FIXME: Implement me!
}

QModelIndex ViewBoard::parent(const QModelIndex &index) const
{
    // FIXME: Implement me!
}

int ViewBoard::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

int ViewBoard::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

QVariant ViewBoard::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return QVariant();
}
