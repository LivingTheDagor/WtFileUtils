

//#include <chrono>
#include "DataBlock.h"
#include <iostream>
#include <fstream>
#include "reader.h"
//#include "rapidjson/rapidjson.h"

bool DataBlock::getStr(int param_number, std::string &out) const {
    if (this->params[param_number]->type != TYPE_STRING) return false;

    out = this->params[param_number]->data.s;
    return true;
}
bool DataBlock::getBool(int param_number, bool &out) const {
    if (this->params[param_number]->type != TYPE_BOOL) return false;
    out = this->params[param_number]->data.b;
    return true;
}
bool DataBlock::getInt(int param_number, int &out) const {
    if (this->params[param_number]->type != TYPE_INT) return false;
    out = this->params[param_number]->data.i;
    return true;
}
bool DataBlock::getReal(int param_number, float &out) const {
    if (this->params[param_number]->type != TYPE_REAL) return false;
    out = this->params[param_number]->data.r;
    return true;
}
bool DataBlock::getPoint2(int param_number, Point2 &out) const {
    if (this->params[param_number]->type != TYPE_POINT2) return false;
    out = this->params[param_number]->data.p2;
    return true;
}
bool DataBlock::getPoint3(int param_number, Point3 &out) const {
    if (this->params[param_number]->type != TYPE_POINT3) return false;
    out = this->params[param_number]->data.p3;
    return true;
}
bool DataBlock::getPoint4(int param_number, Point4 &out) const{
    if (this->params[param_number]->type != TYPE_POINT4) return false;
    out = this->params[param_number]->data.p4;
    return true;
}
bool DataBlock::getIPoint2(int param_number, IPoint2 &out) const {
    if (this->params[param_number]->type != TYPE_IPOINT2) return false;
    out = this->params[param_number]->data.ip2;
    return true;
}
bool DataBlock::getIPoint3(int param_number, IPoint3 &out) const {
    if (this->params[param_number]->type != TYPE_IPOINT3) return false;
    out = this->params[param_number]->data.ip3;
    return true;
}
bool DataBlock::getE3DColor(int param_number, E3DCOLOR &out) const {
    if (this->params[param_number]->type != TYPE_E3DCOLOR) return false;
    out = this->params[param_number]->data.c;
    return true;
}
bool DataBlock::getTMatrix(int param_number, TMatrix &out) const {
    if (this->params[param_number]->type != TYPE_MATRIX) return false;
    out = this->params[param_number]->data.tm;
    return true;
}
bool DataBlock::getStr(const std::string& name, std::string &out, int index) const {
    int name_id_ = getNameIdNoAdd(name);
    Param * obj = getIndexedParam(name_id_, index, TYPE_STRING);
    if (obj)
    {
        out = obj->data.s;
        return true;
    }
    return false;
}
bool DataBlock::getBool(const std::string& name, bool &out, int index) const {
    int name_id_ = getNameIdNoAdd(name);
    Param * obj = getIndexedParam(name_id_, index, TYPE_BOOL);
    if (obj)
    {
        out = obj->data.b;
        return true;
    }
    return false;
}
bool DataBlock::getInt(const std::string& name, int &out, int index) const {
    int name_id_ = getNameIdNoAdd(name);
    Param * obj = getIndexedParam(name_id_, index, TYPE_INT);
    if (obj)
    {
        out = obj->data.i;
        return true;
    }
    return false;
}
bool DataBlock::getReal(const std::string& name, float &out, int index) const {
    int name_id_ = getNameIdNoAdd(name);
    Param * obj = getIndexedParam(name_id_, index, TYPE_REAL);
    if (obj)
    {
        out = obj->data.r;
        return true;
    }
    return false;
}
bool DataBlock::getPoint2(const std::string& name, Point2 &out, int index) const {
    int name_id_ = getNameIdNoAdd(name);
    Param * obj = getIndexedParam(name_id_, index, TYPE_POINT2);
    if (obj)
    {
        out = obj->data.p2;
        return true;
    }
    return false;
}
bool DataBlock::getPoint3(const std::string& name, Point3 &out, int index) const {
    int name_id_ = getNameIdNoAdd(name);
    Param * obj = getIndexedParam(name_id_, index, TYPE_POINT3);
    if (obj)
    {
        out = obj->data.p3;
        return true;
    }
    return false;
}
bool DataBlock::getPoint4(const std::string& name, Point4 &out, int index) const {
    int name_id_ = getNameIdNoAdd(name);
    Param * obj = getIndexedParam(name_id_, index, TYPE_POINT4);
    if (obj)
    {
        out = obj->data.p4;
        return true;
    }
    return false;
}
bool DataBlock::getIPoint2(const std::string& name, IPoint2 &out, int index) const {
    int name_id_ = getNameIdNoAdd(name);
    Param * obj = getIndexedParam(name_id_, index, TYPE_IPOINT2);
    if (obj)
    {
        out = obj->data.ip2;
        return true;
    }
    return false;
}
bool DataBlock::getIPoint3(const std::string& name, IPoint3 &out, int index) const {
    int name_id_ = getNameIdNoAdd(name);
    Param * obj = getIndexedParam(name_id_, index, TYPE_IPOINT3);
    if (obj)
    {
        out = obj->data.ip3;
        return true;
    }
    return false;
}
bool DataBlock::getE3DColor(const std::string& name, E3DCOLOR &out, int index) const {
    int name_id_ = getNameIdNoAdd(name);
    Param * obj = getIndexedParam(name_id_, index, TYPE_E3DCOLOR);
    if (obj)
    {
        out = obj->data.c;
        return true;
    }
    return false;
}
bool DataBlock::getTMatrix(const std::string& name, TMatrix &out, int index) const {
    int name_id_ = getNameIdNoAdd(name);
    Param * obj = getIndexedParam(name_id_, index, TYPE_MATRIX);
    if (obj)
    {
        out = obj->data.tm;
        return true;
    }
    return false;
}

DataBlock::DataBlock() {
    this->name_id = -1;
    this->param_count = 0;
    this->block_count = 0;
    this->nm = std::make_shared<NameMap>();
    //std::cout << "DataBlock ctor 1 " << this->getBlockName() << "\n";
}
DataBlock::DataBlock(int name_id, int prealloc_param, int prealloc_block, const std::shared_ptr<NameMap> &nm) {
    this->name_id = name_id;
    this->param_count = 0;
    this->block_count = 0;
    this->params.reserve(prealloc_param);
    this->blocks.reserve(prealloc_block);
    this->nm = nm;
    //std::cout << "DataBlock ctor 2 " << this->getBlockName() << "\n";
}

DataBlock::DataBlock(const std::shared_ptr<NameMap> &nm) {
    this->name_id = -1;
    this->param_count = 0;
    this->block_count = 0;
    this->nm = nm;
    //std::cout << "DataBlock ctor 3 " << this->getBlockName() << "\n";
}

DataBlock::DataBlock(int prealloc_param, int prealloc_block) {
    this->params.reserve(prealloc_param);
    this->blocks.reserve(prealloc_block);
    this->name_id = -1;
    this->param_count = 0;
    this->block_count = 0;
    this->nm = std::make_shared<NameMap>(NameMap());
    //std::cout << "DataBlock ctor 4 " << this->getBlockName() << "\n";
}

DataBlock::DataBlock(int prealloc_param, int prealloc_block, const std::shared_ptr<NameMap> &nm) {
    this->params.reserve(prealloc_param);
    this->blocks.reserve(prealloc_block);
    this->name_id = -1;
    this->param_count = 0;
    this->block_count = 0;
    this->nm = nm;
    //std::cout << "DataBlock ctor 5 " << this->getBlockName() << "\n";
}


int DataBlock::addStr(int name_id_, const std::string &value) {
    this->param_count += 1;
    std::string copy = value;
    auto p = SharedPtr<Param>::make(name_id_, copy);
    return addParam(p);
}
int DataBlock::addStr(int name_id_, const std::string_view &value) {
    this->param_count += 1;
    auto p = SharedPtr<Param>::make(name_id_, value);
    return addParam(p);
}
int DataBlock::addBool(int name_id_, bool value) {
    this->param_count += 1;
    auto p = SharedPtr<Param>::make(name_id_, value);
    return addParam(p);
}
int DataBlock::addInt(int name_id_, int value) {
    this->param_count += 1;
    auto p = SharedPtr<Param>::make(name_id_, value);
    return addParam(p);
}
int DataBlock::addReal(int name_id_, float value) {
    this->param_count += 1;
    auto p = SharedPtr<Param>::make(name_id_, value);
    return addParam(p);
}
int DataBlock::addPoint2(int name_id_, const Point2 &value) {
    this->param_count += 1;
    auto p = SharedPtr<Param>::make(name_id_, value);
    return addParam(p);
}
int DataBlock::addPoint3(int name_id_, const Point3 &value) {
    this->param_count += 1;
    auto p = SharedPtr<Param>::make(name_id_, value);
    return addParam(p);
}
int DataBlock::addPoint4(int name_id_, const Point4 &value) {
    this->param_count += 1;
    auto p = SharedPtr<Param>::make(name_id_, value);
    return addParam(p);
}
int DataBlock::addIPoint2(int name_id_, const IPoint2 &value) {
    this->param_count += 1;
    auto p = SharedPtr<Param>::make(name_id_, value);
    return addParam(p);
}
int DataBlock::addIPoint3(int name_id_, const IPoint3 &value) {
    this->param_count += 1;
    auto p = SharedPtr<Param>::make(name_id_, value);
    return addParam(p);
}
int DataBlock::addE3DColor(int name_id_, const E3DCOLOR value) {
    this->param_count += 1;
    auto p = SharedPtr<Param>::make(name_id_, value);
    return addParam(p);
}
int DataBlock::addTMatrix(int name_id_, const TMatrix &value) {
    this->param_count += 1;
    auto p = SharedPtr<Param>::make(name_id_, value);
    return addParam(p);
}

int DataBlock::addBlock(int name_id_) {
    SharedPtr blk = SharedPtr(new DataBlock(this->nm));
    blk->name_id = name_id_;
    this->blocks.emplace_back(blk);
    this->block_count++;
    return this->block_count-1;
}


int DataBlock::addBlock(SharedPtr<DataBlock> &blk) {
    blk->updateNameMap(this->nm);
    this->blocks.emplace_back(blk);
    this->block_count++;
    return this->block_count-1;
}

int DataBlock::addBlockUnsafe(SharedPtr<DataBlock> &blk) {
    this->blocks.emplace_back(blk);
    this->block_count++;
    return this->block_count-1;
}

bool DataBlock::updateNameMap(const std::shared_ptr<NameMap> &other)
{
    if(!(this->nm == other))
    {
        for (auto &p : this->params)
        {

            if (p->type == TYPE_NONE) continue;
            std::string_view name = this->getNameFromId(p->name_id);
            p->name_id = other->GetIdFromName(name);
        }
    }
    for (auto &b : this->blocks)
    {
        std::string_view name = this->getNameFromId(b->name_id);
        if(!(this->nm == other))
            b->name_id = other->GetIdFromName(name);
        b->updateNameMap(other);
    }
    this->nm = other;
    return true;
}

void printIndent(int level, std::basic_ostream<char> &out) {
    for (int i = 0; i < level; i++) {
        out << " ";
    }
}


void DataBlock::printBlock(int indent, std::basic_ostream<char> &out) const
{
    for(auto &p : params)
    {
        if (!p) continue;
        printIndent(indent*2, out);
        out << this->getNameFromId(p->name_id) << ":";
        switch (p->type)
        {
            case TYPE_STRING:
                out << "t=" << "\"" << p->data.s << "\"\n";
                break;
            case TYPE_BOOL:
            {
                char buf[4];
                sprintf(buf, "%s", p->data.b ? "yes" : "no");
                out << "b=" << buf << "\n";
            }
            break;
            case TYPE_INT:
            {
                char buf[32];
                sprintf(buf, "%d", p->data.i);
                out << "i=" << buf << "\n";
            }
            break;
            case TYPE_REAL:
            {
                char buf[64];
                sprintf(buf, "%g", p->data.r);
                out << "r=" << buf << "\n";
            }
            break;
            case TYPE_POINT2:
            {
                char buf[128];
                sprintf(buf, "%g, %g", p->data.p2.x, p->data.p2.y);
                out << "p2=" << buf << "\n";
            }
            break;
            case TYPE_POINT3:
            {
                char buf[128];
                sprintf(buf, "%g, %g, %g", p->data.p3.x, p->data.p3.y, p->data.p3.z);
                out << "p3=" << buf << "\n";
            }
            break;
            case TYPE_POINT4:
            {
                char buf[160];
                sprintf(buf, "%g, %g, %g, %g", p->data.p4.x, p->data.p4.y, p->data.p4.z, p->data.p4.w);
                out << "p4=" << buf << "\n";
            }
            break;
            case TYPE_IPOINT2:
            {
                char buf[128];
                sprintf(buf, "%d, %d", p->data.ip2.x, p->data.ip2.y);
                out << "ip2=" << buf << "\n";
            }
            break;
            case TYPE_IPOINT3:
            {
                char buf[128];
                sprintf(buf, "%d, %d, %d", p->data.ip3.x, p->data.ip3.y, p->data.ip3.z);
                out << "ip3=" << buf << "\n";
            }
            break;
            case TYPE_E3DCOLOR:
            {
                char buf[128];
                sprintf(buf, "%d, %d, %d, %d", p->data.c.r, p->data.c.g, p->data.c.b, p->data.c.a);
                out << "c=" << buf << "\n";
            }
            break;
            case TYPE_MATRIX:
            {
                char buf[256];
                sprintf(buf, "[[%g, %g, %g] [%g, %g, %g] [%g, %g, %g] [%g, %g, %g]]", p->data.tm.x1.x, p->data.tm.x1.y,
                        p->data.tm.x1.z, p->data.tm.x2.x, p->data.tm.x2.y, p->data.tm.x2.z, p->data.tm.x3.x,
                        p->data.tm.x3.y, p->data.tm.x3.z, p->data.tm.x4.x, p->data.tm.x4.y, p->data.tm.x4.z);
                out << "m=" << buf << "\n";
            }
            break;
        }
    }
    for(auto &b : this->blocks) {
        if(!b) continue;
        printIndent(indent*2, out);
        out << b->getBlockName() << "{\n";
        b->printBlock(indent+1, out);
        printIndent(indent*2, out);
        out << "}\n";
    }
}
void fwrite(const char * w, size_t size, [[maybe_unused]] size_t count, std::ostream *cb)
{
    cb->write(w, (std::streamsize)size);
}

static void writeIndent(std::ostream *cb, int n)
{
    if (n <= 0)
        return;
    for (; n >= 8; n -= 8)
        fwrite("        ", 8, 1, cb);
    for (; n >= 2; n -= 2)
        fwrite("  ", 2, 1, cb);
    for (; n >= 1; n--)
        fwrite(" ", 1, 1, cb);
}

static void writeString(std::ostream *cb, const char *s)
{
    if (!s || !*s)
        return;
    int l = (int)strlen(s);
    fwrite(s, l, 1, cb);
}

static void writeStringValue(std::ostream *cb, const char *s)
{
    if (!s)
        s = "";

    fwrite("\"", 1, 1, cb);

    for (; *s; ++s)
    {
        char c = *s;
        if (c == '~')
            fwrite("~~", 2, 1, cb);
        else if (c == '"')
            fwrite("~\"", 2, 1, cb);
        else if (c == '\r')
            fwrite("~r", 2, 1, cb);
        else if (c == '\n')
            fwrite("~n", 2, 1, cb);
        else if (c == '\t')
            fwrite("~t", 2, 1, cb);
        else
            fwrite(&c, 1, 1, cb);
    }
    fwrite("\"", 1, 1, cb);
}

/*DLLEXPORT*/ void DataBlock::saveText(std::ostream *cb, int level) const
{
    int i;
    for (i = 0; i < (int)params.size(); ++i)
    {
        Param p = *params[i].get();

        writeIndent(cb, level * 2);
        writeString(cb, this->getNameFromId(p.name_id).data());
        switch (p.type)
        {
            case TYPE_STRING:
                writeString(cb, ":t=");
                writeStringValue(cb, p.data.s.data());
                break;
            case TYPE_BOOL:
            {
                writeString(cb, ":b=");
                char buf[32];
                sprintf(buf, "%s", p.data.b ? "yes" : "no");
                writeString(cb, buf);
            }
                break;
            case TYPE_INT:
            {
                writeString(cb, ":i=");
                char buf[32];
                sprintf(buf, "%d", p.data.i);
                writeString(cb, buf);
            }
                break;
            case TYPE_REAL:
            {
                writeString(cb, ":r=");
                char buf[64];
                sprintf(buf, "%g", p.data.r);
                writeString(cb, buf);
            }
                break;
            case TYPE_POINT2:
            {
                writeString(cb, ":p2=");
                char buf[128];
                sprintf(buf, "%g, %g", p.data.p2.x, p.data.p2.y);
                writeString(cb, buf);
            }
                break;
            case TYPE_POINT3:
            {
                writeString(cb, ":p3=");
                char buf[128];
                sprintf(buf, "%g, %g, %g", p.data.p3.x, p.data.p3.y, p.data.p3.z);
                writeString(cb, buf);
            }
                break;
            case TYPE_POINT4:
            {
                writeString(cb, ":p4=");
                char buf[160];
                sprintf(buf, "%g, %g, %g, %g", p.data.p4.x, p.data.p4.y, p.data.p4.z, p.data.p4.w);
                writeString(cb, buf);
            }
                break;
            case TYPE_IPOINT2:
            {
                writeString(cb, ":ip2=");
                char buf[128];
                sprintf(buf, "%d, %d", p.data.ip2.x, p.data.ip2.y);
                writeString(cb, buf);
            }
                break;
            case TYPE_IPOINT3:
            {
                writeString(cb, ":ip3=");
                char buf[128];
                sprintf(buf, "%d, %d, %d", p.data.ip3.x, p.data.ip3.y, p.data.ip3.z);
                writeString(cb, buf);
            }
                break;
            case TYPE_E3DCOLOR:
            {
                writeString(cb, ":c=");
                char buf[128];
                sprintf(buf, "%d, %d, %d, %d", p.data.c.r, p.data.c.g, p.data.c.b, p.data.c.a);
                writeString(cb, buf);
            }
                break;
            case TYPE_MATRIX:
            {
                writeString(cb, ":m=");
                char buf[256];
                sprintf(buf, "[[%g, %g, %g] [%g, %g, %g] [%g, %g, %g] [%g, %g, %g]]", p.data.tm.x1.x, p.data.tm.x1.y,
                        p.data.tm.x1.z, p.data.tm.x2.x, p.data.tm.x2.y, p.data.tm.x2.z, p.data.tm.x3.x,
                        p.data.tm.x3.y, p.data.tm.x3.z, p.data.tm.x4.x, p.data.tm.x4.y, p.data.tm.x4.z);
                writeString(cb, buf);
                break;
            }
        }
        fwrite("\n", 1, 1, cb);
    }

    if (params.size() && blocks.size())
    {
        writeIndent(cb, level * 2);
        fwrite("\n", 1, 1, cb);
    }
    for (i = 0; i < (int)blocks.size(); ++i)
    {
        DataBlock &b = *blocks[i];

        writeIndent(cb, level * 2);
        writeString(cb, getNameFromId(b.name_id).data());
        fwrite("{\n", 2, 1, cb);

        b.saveText(cb, level + 1);

        writeIndent(cb, level * 2);
        fwrite("}\n", 2, 1, cb);

        if (i != (int)blocks.size() - 1)
            fwrite("\n", 1, 1, cb);
    }
}




int DataBlock::getIdFromName(const std::string &name) {
    return this->nm->GetIdFromName(name);
}

DataBlock * DataBlock::getBlock(const std::string &name, int index) {
    int nid = this->getIdFromName(name);
    int c = 0;
    for(auto &b : this->blocks)
    {
        if(!b) continue;
        if(b->name_id==nid)
        {
            if (c>=index)
                return b.get();
            c++;
        }
    }
    return nullptr;
}

DataBlock *DataBlock::getBlock(int param_index) {
    return this->blocks[param_index].get();
}


