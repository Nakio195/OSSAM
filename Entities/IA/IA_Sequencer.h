#ifndef IA_SEQUENCER_H
#define IA_SEQUENCER_H

#include "IA_Node.h"


template<typename T>
class IA_Sequencer
{
    public:
        enum SequenceMode{Single = 1, Repeat = 2};

    public:
        IA_Sequencer();
        ~IA_Sequencer();

        void AddNode(IA_Node<T> NewNode);
        IA_Node<T> getCurrentNode();

        void Start();
        void Stop();
        void Clear();
        void Play(float ElapsedTime);

    public:
        unsigned int Mode;

    private:
        float TempoDelay;
        unsigned int CurrentNode;
        std::vector<IA_Node<T>> Sequence;
        bool Running;

};


#endif // IA_SEQUENCER_H
