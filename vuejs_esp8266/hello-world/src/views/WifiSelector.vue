<template>
  <el-drawer
  :append-to-body="true"
  title="I am the title"
  :visible.sync="drawer"
  direction="rtl">
    <el-table
      :data="getNearWifi"
      style="width: 100%">
      <el-table-column
        prop="ssid"
        label="Wifi"
        width="180">
      </el-table-column>
      <el-table-column
        prop="rssi"
        label="Sóng"
        width="180">
      </el-table-column>
    </el-table>
</el-drawer>
</template>

<script>
import {mapGetters} from 'vuex'
export default {
    data: function(){
        return {
            drawer: true
        }
    },
    computed:{
      ...mapGetters(['getNearWifi'])
    },
    mounted:function(){
        console.log("mount")
      this.$store.dispatch('updateNearWifi')
    },
}
</script>

<style>

</style>