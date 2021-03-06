#include "DeviceTableModel.h"
#include "CentralWidget.h"

const static int NCOLUMNS = 6;

DeviceTableModel::DeviceTableModel()
    : _entries()
    , _errors() {

    try {
        auto opencl_devices = GPUInfo::getOpenCLDevices();
        _entries.insert(_entries.end(), opencl_devices.begin(), opencl_devices.end());
        auto cuda_devices = GPUInfo::getCUDADevices();
        _entries.insert(_entries.end(), cuda_devices.begin(), cuda_devices.end());
    } catch (const std::runtime_error & e) {
        _errors.push_back(e);
    }
}

const std::vector<Device> & DeviceTableModel::entries() const {
    const std::vector<Device> & ret = _entries;
    return ret;
}

const std::vector<std::runtime_error> & DeviceTableModel::errors() const {
    return _errors;
}


int DeviceTableModel::rowCount(const QModelIndex & parent) const {
    return _entries.size();
}

int DeviceTableModel::columnCount(const QModelIndex & parent) const {
    return NCOLUMNS;
}

QVariant DeviceTableModel::data(const QModelIndex & index, int role) const {
    if (!index.isValid())
        return QVariant();

    if (index.row() < 0 || ((unsigned) index.row() >= _entries.size()))
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    auto & item = _entries.at(index.row());
    switch (index.column()) {
    case 0:
        return QString::fromStdString(item.device());
    case 1:
        return QString::fromStdString(item.platform());
    case 2:
        return item.device_id();
    case 3:
        if (item.platform() == "OpenCL")
            return item.platform_id();
        else
            return QVariant();
    case 4:
        return QString::fromStdString(item.platform_version);
    case 5:
        return QString::fromStdString(item.device_version);
    default:
        return QVariant();
    }
}


QVariant DeviceTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    if (orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return QString("Device");
        case 1:
            return QString("Platform");
        case 2:
            return QString("Device ID");
        case 3:
            return QString("Platform ID");
        case 4:
            return QString("Platform version");
        case 5:
            return QString("Device version");
        default:
            return QVariant();
        }
    } else {
        return QString("%1").arg(section);
    }
}


#include "DeviceTableModel.moc"
